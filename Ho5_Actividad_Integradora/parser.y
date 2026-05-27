%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_number;
extern FILE *yyin;

void yyerror(const char *msg);

#define MAX_SYMBOLS 1000
#define MAX_SCOPES 100

typedef struct {
    char nombre[256];
    char clase[50];      // variable, función, macro
    char tipo[50];       // int, etc
    int ambito;          // 0 = global, >0 = local
    int aridad;          // para funciones
    int usado;           // 1 si se usó, 0 si no
    int linea;           // línea de declaración
} Simbolo;

Simbolo tabla_simbolos[MAX_SYMBOLS];
int num_simbolos = 0;
int ambito_actual = 0;
int scope_stack[MAX_SCOPES];
int scope_depth = 0;

int error_count = 0;
int warning_count = 0;
int param_count = 0;          // Contador de parámetros
int arg_count = 0;            // Contador de argumentos
char current_function[256];   // Función actual siendo procesada

void agregar_simbolo(const char *nombre, const char *clase, const char *tipo, int aridad);
void usar_simbolo(const char *nombre);
Simbolo* buscar_simbolo(const char *nombre, int buscar_ambito_actual);
void entrar_ambito();
void salir_ambito();
void imprimir_tabla_simbolos();
void marcar_variables_no_usadas();
void verificar_aridad(const char *nombre, int aridad_esperada);

%}

%union {
    char *str;
    int num;
    struct {
        int count;
    } args;
}

%token INCLUDE DEFINE INT FUNC RETURN IF
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA ASSIGN DOT
%token LT GT PLUS MINUS MULT DIV
%token <str> IDENTIFIER STRING
%token <num> NUMBER

%type <str> statement_list statement declaration assignment expr

%%

programa: preprocesador declaraciones funciones
        ;

preprocesador: /* vacío */
             | preprocesador INCLUDE LT IDENTIFIER GT
             | preprocesador DEFINE IDENTIFIER NUMBER
               {
                   agregar_simbolo($3, "macro", "int", 0);
               }
             | preprocesador DEFINE IDENTIFIER STRING
               {
                   agregar_simbolo($3, "macro", "string", 0);
               }
             ;

declaraciones: /* vacío */
             | declaraciones INT IDENTIFIER SEMICOLON
               {
                   agregar_simbolo($3, "variable", "int", 0);
               }
             ;

funciones: /* vacío */
         | funciones funcion
         ;

funcion: FUNC IDENTIFIER LPAREN
         {
             param_count = 0;
             strcpy(current_function, $2);
         }
         parametros RPAREN
         {
             // Guardar función con su aridad
             agregar_simbolo(current_function, "función", "int", param_count);
             entrar_ambito();
         }
         LBRACE block RBRACE
         {
             salir_ambito();
         }
       ;

parametros: /* vacío */
          | parametro_list
          ;

parametro_list: IDENTIFIER
                {
                    param_count++;
                    agregar_simbolo($1, "variable", "int", 0);
                }
              | parametro_list COMMA IDENTIFIER
                {
                    param_count++;
                    agregar_simbolo($3, "variable", "int", 0);
                }
              ;

block: statement_list
     ;

statement_list: /* vacío */
              | statement_list statement
              ;

statement: declaration
         | assignment
         | if_statement
         | function_call
         | return_statement
         ;

declaration: INT IDENTIFIER SEMICOLON
             {
                 agregar_simbolo($2, "variable", "int", 0);
             }
           ;

assignment: IDENTIFIER ASSIGN expr SEMICOLON
            {
                usar_simbolo($1);
            }
          ;

expr: IDENTIFIER
      {
          usar_simbolo($1);
          $$ = $1;
      }
    | NUMBER
      {
          $$ = malloc(20);
          sprintf($$, "%d", $1);
      }
    | expr PLUS expr
    | expr MINUS expr
    | expr MULT expr
    | expr DIV expr
    | LPAREN expr RPAREN
    ;

if_statement: IF LPAREN IDENTIFIER RPAREN
              {
                  usar_simbolo($3);
              }
              LBRACE
              {
                  entrar_ambito();
              }
              statement_list RBRACE
              {
                  salir_ambito();
              }
            ;

function_call: IDENTIFIER LPAREN
               {
                   arg_count = 0;
                   strcpy(current_function, $1);
                   usar_simbolo($1);
               }
               arguments RPAREN SEMICOLON
               {
                   verificar_aridad(current_function, arg_count);
               }
             ;

arguments: /* vacío */
         | argument_list
         ;

argument_list: IDENTIFIER
               {
                   arg_count++;
                   usar_simbolo($1);
               }
             | argument_list COMMA IDENTIFIER
               {
                   arg_count++;
                   usar_simbolo($3);
               }
             ;

return_statement: RETURN IDENTIFIER SEMICOLON
                  {
                      usar_simbolo($2);
                  }
                | RETURN NUMBER SEMICOLON
                ;

%%

void agregar_simbolo(const char *nombre, const char *clase, const char *tipo, int aridad) {
    // Para funciones, buscar en ámbito global
    // Para variables, buscar en ámbito actual
    int scope_to_check = strcmp(clase, "función") == 0 ? 0 : ambito_actual;
    
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0 && 
            tabla_simbolos[i].ambito == scope_to_check) {
            error_count++;
            fprintf(stderr, "Error semántico en línea %d: %s '%s' ya declarada\n", 
                    line_number, clase, nombre);
            return;
        }
    }
    
    if (num_simbolos >= MAX_SYMBOLS) {
        fprintf(stderr, "Error: tabla de símbolos llena\n");
        return;
    }
    
    strcpy(tabla_simbolos[num_simbolos].nombre, nombre);
    strcpy(tabla_simbolos[num_simbolos].clase, clase);
    strcpy(tabla_simbolos[num_simbolos].tipo, tipo);
    tabla_simbolos[num_simbolos].ambito = scope_to_check;
    tabla_simbolos[num_simbolos].aridad = aridad;
    tabla_simbolos[num_simbolos].usado = 0;
    tabla_simbolos[num_simbolos].linea = line_number;
    
    num_simbolos++;
}

void usar_simbolo(const char *nombre) {
    // Buscar primero en el ámbito actual y hacia arriba
    for (int i = num_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0) {
            // Para funciones, deben estar en ámbito global (0)
            // Para variables, pueden estar en el ámbito actual o superior
            if (tabla_simbolos[i].ambito == 0 || tabla_simbolos[i].ambito <= ambito_actual) {
                tabla_simbolos[i].usado = 1;
                return;
            }
        }
    }
    
    error_count++;
    fprintf(stderr, "Error semántico en línea %d: variable '%s' no declarada\n", 
            line_number, nombre);
}

Simbolo* buscar_simbolo(const char *nombre, int buscar_ambito_actual) {
    for (int i = num_simbolos - 1; i >= 0; i--) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0) {
            if (!buscar_ambito_actual || tabla_simbolos[i].ambito == ambito_actual) {
                return &tabla_simbolos[i];
            }
        }
    }
    return NULL;
}

void entrar_ambito() {
    ambito_actual++;
}

void salir_ambito() {
    ambito_actual--;
}

void marcar_variables_no_usadas() {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].clase, "variable") == 0 && 
            tabla_simbolos[i].usado == 0) {
            warning_count++;
            fprintf(stderr, "Advertencia: variable '%s' declarada pero no usada\n",
                    tabla_simbolos[i].nombre);
        }
    }
}

void verificar_aridad(const char *nombre, int aridad_esperada) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].nombre, nombre) == 0 &&
            strcmp(tabla_simbolos[i].clase, "función") == 0) {
            if (tabla_simbolos[i].aridad != aridad_esperada) {
                error_count++;
                fprintf(stderr, "Error semántico en línea %d: función '%s' espera %d argumento(s), pero recibió %d\n",
                        line_number, nombre, tabla_simbolos[i].aridad, aridad_esperada);
            }
            return;
        }
    }
}

void imprimir_tabla_simbolos() {
    printf("\n+----+---------+--------+--------+--------+---------+\n");
    printf("| No | Nombre  | Clase  | Tipo   | Ámbito | Aridad  |\n");
    printf("+----+---------+--------+--------+--------+---------+\n");
    
    for (int i = 0; i < num_simbolos; i++) {
        printf("| %2d | %-7s | %-6s | %-6s | %6d | %7d |\n",
               i + 1,
               tabla_simbolos[i].nombre,
               tabla_simbolos[i].clase,
               tabla_simbolos[i].tipo,
               tabla_simbolos[i].ambito,
               tabla_simbolos[i].aridad);
    }
    
    printf("+----+---------+--------+--------+--------+---------+\n\n");
}

void yyerror(const char *msg) {
    error_count++;
    fprintf(stderr, "Error sintáctico en línea %d: %s\n", line_number, msg);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s archivo.c\n", argv[0]);
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Error: no se puede abrir el archivo '%s'\n", argv[1]);
        return 1;
    }
    
    yyin = f;
    yyparse();
    fclose(f);
    
    printf("\n=== TABLA DE SÍMBOLOS ===\n");
    imprimir_tabla_simbolos();
    
    marcar_variables_no_usadas();
    
    printf("\n=== RESUMEN ===\n");
    printf("Total de errores semánticos: %d\n", error_count);
    printf("Total de advertencias: %d\n", warning_count);
    
    return error_count > 0 ? 1 : 0;
}
