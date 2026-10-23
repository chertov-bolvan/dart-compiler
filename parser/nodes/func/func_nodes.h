

typedef struct FuncDeclNode {
  int id;

  char* identifier;
  struct TypeNode* type;

  struct ParamNode* parameters;
  struct StmtNode* body;
} FuncDeclNode;

FuncDeclNode* createFuncDecl(TypeNode* type, char* identifier, ParamNode* parameters, StmtNode* body);


typedef struct ParamNode {
  int id;

  struct TypeNode* type;
  char* identifier;

  struct ParamNode* next;
} ParamNode;

ParamNode* createParam(TypeNode* type, char* identifier);
ParamNode* addParamToList(ParamNode* list, ParamNode* newParam);