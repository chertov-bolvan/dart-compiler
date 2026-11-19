#include "tree_dot_visual.h"

static void printText(const char* text) {
    if (!text) return;
    for (; *text; ++text) {
        switch (*text) {
            case '"': printf("%s", "\\\""); break;
            case '\\': printf("%s", "\\\\"); break;
            case '\n': printf("%s", "\\n"); break;
            case '\r': printf("%s", "\\r"); break;
            case '\t': printf("%s", "    "); break;
            default: printf("%c", *text); break;
        }
    }
}

static void label(int id, const char* title, const char* value) {
    printf("%d [label=\"", id);
    printText(title);
    if (value) {
        printf("%s", ": ");
        printText(value);
    }
    printf("%s", "\" fontname=\"courier\" shape=rect];\n");
}

static void edge(int from, int to, const char* title) {
    printf("%d -> %d [label=\"%s\"];\n", from, to, title);
}

static void indexedEdge(int from, int to, const char* title, int index) {
    printf("%d -> %d [label=\"%s %d\"];\n", from, to, title, index);
}

static const char* modifierName(VarDeclModifier modifier) {
    switch (modifier) {
        case NoModifier: return "var";
        case FinalModifier: return "final";
        case ConstModifier: return "const";
    }
    return "unknown";
}

void printProgramDot(ProgramNode* node) {
    printf("%s", "digraph {\n");
    if (node) {
        label(node->nodeId, "PROGRAM", NULL);
        int index = 1;
        for (TopLevelDeclNode* item = node->topLevelDeclNode; item; item = item->next) {
            indexedEdge(node->nodeId, item->nodeId, "declaration", index++);
            printTopLevelDeclDot(item);
        }
    }
    printf("%s", "}\n");
}

void printTopLevelDeclDot(TopLevelDeclNode* node) {
    if (!node) return;
    switch (node->type) {
        case TopLevelVarDeclType:
            label(node->nodeId, "Global variable declaration", NULL);
            edge(node->nodeId, node->varDeclNode->nodeId, "variable");
            printVarDeclDot(node->varDeclNode);
            break;
        case TopLevelFuncDeclType:
            label(node->nodeId, "Global function declaration", NULL);
            edge(node->nodeId, node->funcDeclNode->nodeId, "function");
            printFuncDeclDot(node->funcDeclNode);
            break;
        case TopLevelClassDeclType:
            label(node->nodeId, "Global class declaration", NULL);
            edge(node->nodeId, node->classDeclNode->nodeId, "class");
            printClassDeclDot(node->classDeclNode);
            break;
    }
}

void printTypeDot(TypeNode* node) {
    if (!node) return;
    switch (node->type) {
        case IdTType: label(node->nodeId, "Type", node->id); break;
        case VoidTType: label(node->nodeId, "Type", "void"); break;
        case ListTType:
            label(node->nodeId, "Type", "List");
            if (node->innerType) {
                edge(node->nodeId, node->innerType->nodeId, "inner type");
                printTypeDot(node->innerType);
            }
            break;
    }
}

void printExprDot(ExprNode* node) {
    if (!node) return;
    const char* title = "Expression";
    const char* value = node->id;
    switch (node->type) {
        case IntType:
            title = "Int"; break;
        case DoubleType:
            title = "Double"; break;
        case BoolType: title = "Bool"; value = node->boolValue ? "true" : "false"; break;
        case StringType: title = "String"; value = node->strValue; break;
        case IdType: title = "Id"; break;
        case NullType: title = "null"; break;
        case ThisType: title = "this"; break;
        case SuperType: title = "super"; break;
        case ListLiteralType: title = "List literal"; break;
        case IncPostfixType: title = "postfix ++"; break;
        case DecPostfixType: title = "postfix --"; break;
        case IncPrefixType: title = "prefix ++"; break;
        case DecPrefixType: title = "prefix --"; break;
        case UminusType: title = "unary -"; break;
        case NotType: title = "!"; break;
        case AccessFieldType: title = "Field access"; break;
        case ThisAccessFieldType: title = "this field"; break;
        case SuperAccessFieldType: title = "super field"; break;
        case ThisFuncType: title = "this()"; break;
        case SuperFuncType: title = "super()"; break;
        case FuncType: title = "Function call"; break;
        case MethodType: title = "Method call"; break;
        case ThisMethodType: title = "this method"; break;
        case SuperMethodType: title = "super method"; break;
        case NewClassType: title = "new"; break;
        case AccessArrElementType: title = "[]"; break;
        case MulType: title = "*"; break;
        case DivType: title = "/"; break;
        case ModType: title = "%"; break;
        case IntDivType: title = "~/"; break;
        case AddType: title = "+"; break;
        case MinusType: title = "-"; break;
        case LessType: title = "<"; break;
        case GreaterType: title = ">"; break;
        case LEqType: title = "<="; break;
        case GEqType: title = ">="; break;
        case IsType: title = "is"; break;
        case AsType: title = "as"; break;
        case NIsType: title = "is!"; break;
        case EqEqType: title = "=="; break;
        case NEqType: title = "!="; break;
        case LogAndType: title = "&&"; break;
        case LogOrType: title = "||"; break;
        case TernaryOperatorType: title = "?:"; break;
        case AddAssignType: title = "+="; break;
        case SubAssignType: title = "-="; break;
        case MulAssignType: title = "*="; break;
        case DivAssignType: title = "/="; break;
        case ModAssignType: title = "%="; break;
        case IntDivAssignType: title = "~/="; break;
        case EqType: title = "="; break;
    }

    printf("%d [label=\"", node->nodeId);
    printText(title);
    if (node->type == IntType) {
        printf(": %d", node->intValue);
    } else if (node->type == DoubleType) {
        printf(": %.17g", node->doubleValue);
    } else if (value) {
        printf(": ");
        printText(value);
    }
    if (node->constructName) { printf("%c", '.'); printText(node->constructName); }
    if (node->insideParens) printf("%s", " (parenthesized)");
    printf("%s", "\" fontname=\"courier\" shape=rect];\n");

    if (node->type == ListLiteralType) {
        int index = 1;
        for (ExprNode* item = node->left; item; item = item->next) {
            indexedEdge(node->nodeId, item->nodeId, "element", index++);
            printExprDot(item);
        }
    } else if (node->left) {
        edge(node->nodeId, node->left->nodeId,
             node->type == TernaryOperatorType ? "condition" : "left");
        printExprDot(node->left);
    }
    if (node->center) {
        edge(node->nodeId, node->center->nodeId, "true expression");
        printExprDot(node->center);
    }
    if (node->right) {
        edge(node->nodeId, node->right->nodeId,
             node->type == TernaryOperatorType ? "false expression" : "right");
        printExprDot(node->right);
    }
    if (node->typeNode) {
        edge(node->nodeId, node->typeNode->nodeId, "type");
        printTypeDot(node->typeNode);
    }
    int index = 1;
    for (ArgNode* item = node->args; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "argument", index++);
        printArgDot(item);
    }
}

void printArgDot(ArgNode* node) {
    if (!node) return;
    label(node->nodeId, node->name ? "Named argument" : "Argument", node->name);
    if (node->value) {
        edge(node->nodeId, node->value->nodeId, "value");
        printExprDot(node->value);
    }
}

void printVarDeclaratorDot(VarDeclaratorNode* node) {
    if (!node) return;
    label(node->nodeId, "Variable", node->id);
    if (node->init) {
        edge(node->nodeId, node->init->nodeId, "initializer");
        printExprDot(node->init);
    }
}

void printVarDeclDot(VarDeclNode* node) {
    if (!node) return;
    label(node->nodeId, "Variable declaration", modifierName(node->modifier));
    if (node->type) {
        edge(node->nodeId, node->type->nodeId, "type");
        printTypeDot(node->type);
    }
    int index = 1;
    for (VarDeclaratorNode* item = node->declarators; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "variable", index++);
        printVarDeclaratorDot(item);
    }
}

void printForInVarDot(ForInVarNode* node) {
    if (!node) return;
    label(node->nodeId, node->varType == ExistingVarType ? "Existing variable" : modifierName(node->modifier), node->id);
    if (node->type) {
        edge(node->nodeId, node->type->nodeId, "type");
        printTypeDot(node->type);
    }
}

void printStmtDot(StmtNode* node) {
    if (!node) return;
    const char* title = "Statement";
    switch (node->type) {
        case VarDeclType: title = "Variable declaration statement"; break;
        case ExprType: title = "Expression statement"; break;
        case EmptyType: title = "Empty statement"; break;
        case ForType: title = "For"; break;
        case ForInType: title = "For in"; break;
        case WhileType: title = "While"; break;
        case DoWhileType: title = "Do while"; break;
        case IfType: title = "If"; break;
        case ReturnType: title = "Return"; break;
        case BlockType: title = "Block"; break;
        case BreakType: title = "Break"; break;
        case ContinueType: title = "Continue"; break;
    }
    label(node->nodeId, title, NULL);
    if (node->exprNode) {
        const char* role = "condition";
        if (node->type == ExprType || node->type == ReturnType) role = "expression";
        if (node->type == ForInType) role = "iterable";
        edge(node->nodeId, node->exprNode->nodeId, role);
        printExprDot(node->exprNode);
    }
    if (node->varDeclNode) {
        edge(node->nodeId, node->varDeclNode->nodeId, "declaration");
        printVarDeclDot(node->varDeclNode);
    }
    if (node->trueBranch) {
        edge(node->nodeId, node->trueBranch->nodeId, "true branch");
        printStmtDot(node->trueBranch);
    }
    if (node->falseBranch) {
        edge(node->nodeId, node->falseBranch->nodeId, "false branch");
        printStmtDot(node->falseBranch);
    }
    if (node->forInit) {
        edge(node->nodeId, node->forInit->nodeId, "initializer");
        printStmtDot(node->forInit);
    }
    if (node->forInVar) {
        edge(node->nodeId, node->forInVar->nodeId, "loop variable");
        printForInVarDot(node->forInVar);
    }
    int index = 1;
    for (ExprNode* item = node->forUpd; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "update", index++);
        printExprDot(item);
    }
    index = 1;
    for (StmtNode* item = node->body; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, node->type == BlockType ? "statement" : "body", index++);
        printStmtDot(item);
    }
}

void printParamDot(ParamNode* node) {
    if (!node) return;
    const char* title = "Parameter";
    switch (node->paramType) {
        case RequiredPositionalType: title = "Required positional parameter"; break;
        case OptionalPositionType: title = "Optional positional parameter"; break;
        case RequiredNamedType: title = "Required named parameter"; break;
        case OptionalNamedType: title = "Optional named parameter"; break;
    }
    label(node->nodeId, title, node->id);
    if (node->type) {
        edge(node->nodeId, node->type->nodeId, "type");
        printTypeDot(node->type);
    }
    if (node->defaultValue) {
        edge(node->nodeId, node->defaultValue->nodeId, "default value");
        printExprDot(node->defaultValue);
    }
}

void printFuncDeclDot(FuncDeclNode* node) {
    if (!node) return;
    label(node->nodeId, "Function", node->id);
    if (node->type) {
        edge(node->nodeId, node->type->nodeId, "return type");
        printTypeDot(node->type);
    }
    int index = 1;
    for (ParamNode* item = node->parameters; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "parameter", index++);
        printParamDot(item);
    }
    if (node->body) {
        edge(node->nodeId, node->body->nodeId, "body");
        printStmtDot(node->body);
    }
}

void printClassDeclDot(ClassDeclNode* node) {
    if (!node) return;
    const char* title = "Class";
    switch (node->classModifier) {
        case NoClassModifier: break;
        case AbstractClassModifier: title = "Abstract class"; break;
        case FinalClassModifier: title = "Final class"; break;
        case AbstractFinalClassModifier: title = "Abstract final class"; break;
    }
    printf("%d [label=\"%s: ", node->nodeId, title);
    printText(node->id);
    if (node->parentId) { printf("%s", " extends "); printText(node->parentId); }
    printf("%s", "\" fontname=\"courier\" shape=rect];\n");
    int index = 1;
    for (ClassMemberNode* item = node->classMembers; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "member", index++);
        printClassMemberDot(item);
    }
}

void printClassMemberDot(ClassMemberNode* node) {
    if (!node) return;
    const char* title = "Member";
    switch (node->type) {
        case FieldMemberType: title = "Field"; break;
        case MethodMemberType: title = "Method"; break;
        case GetterMemberType: title = "Getter"; break;
        case SetterMemberType: title = "Setter"; break;
        case ConstructorMemberType: title = "Constructor member"; break;
    }
    label(node->nodeId, title, node->isStatic ? "static" : NULL);
    if (node->varDeclNode) {
        edge(node->nodeId, node->varDeclNode->nodeId, "field");
        printVarDeclDot(node->varDeclNode);
    }
    if (node->funcDeclNode) {
        edge(node->nodeId, node->funcDeclNode->nodeId, "function");
        printFuncDeclDot(node->funcDeclNode);
    }
    if (node->constructorDeclNode) {
        edge(node->nodeId, node->constructorDeclNode->nodeId, "constructor");
        printConstructorDeclDot(node->constructorDeclNode);
    }
}

void printConstructorDeclDot(ConstructorDeclNode* node) {
    if (!node) return;
    printf("%d [label=\"Constructor: ", node->nodeId);
    printText(node->id);
    if (node->constructorName) { printf("%c", '.'); printText(node->constructorName); }
    printf("%s", "\" fontname=\"courier\" shape=rect];\n");
    int index = 1;
    for (ParamNode* item = node->parameters; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "parameter", index++);
        printParamDot(item);
    }
    if (node->superConstructor) {
        edge(node->nodeId, node->superConstructor->nodeId, "super constructor");
        printSuperConstructorDot(node->superConstructor);
    }
    if (node->body) {
        edge(node->nodeId, node->body->nodeId, "body");
        printStmtDot(node->body);
    }
}

void printSuperConstructorDot(SuperConstructorNode* node) {
    if (!node) return;
    label(node->nodeId, "Super constructor", node->constructorName);
    int index = 1;
    for (ArgNode* item = node->arguments; item; item = item->next) {
        indexedEdge(node->nodeId, item->nodeId, "argument", index++);
        printArgDot(item);
    }
}
