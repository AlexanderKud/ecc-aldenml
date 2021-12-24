import json
import sys
import re


class ParamComment:
    def __init__(self, ast):
        self.ast = ast
        self.name = ast["param"]
        self.direction = ast["direction"]

    def comment_text(self):
        return self.ast["inner"][0]["inner"][0]["text"].strip()


class FullComment:
    def __init__(self, ast):
        self.ast = ast

    def comment_text(self):
        paragraphs = list(map(
            lambda e: e["inner"][0]["text"].strip(),
            filter(lambda e: e["kind"] == "ParagraphComment", self.ast["inner"])
        ))
        return "\n\n".join(filter(None, paragraphs))

    def comment_params(self):
        return list(map(
            lambda e: ParamComment(e),
            filter(lambda e: e["kind"] == "ParamCommandComment", self.ast["inner"])
        ))


class ParmVarDecl:
    def __init__(self, ast, comment):
        self.ast = ast
        self.name = ast["name"]
        self.mangledName = ast["mangledName"]
        self.comment = comment

    def size(self):
        text = self.comment.comment_text()
        match = re.search(r"\bsize:(\w+)\b", text)
        return match.group(1)


class FunctionDecl:
    def __init__(self, ast):
        self.ast = ast
        self.name = ast["name"]
        self.mangledName = ast["mangledName"]

    def params(self):
        comments = self.comment().comment_params()
        return list(map(
            lambda e: ParmVarDecl(e, next(filter(lambda c: c.name == e["name"], comments))),
            filter(lambda e: e["kind"] == "ParmVarDecl", self.ast["inner"])
        ))

    def comment(self):
        return list(map(
            lambda e: FullComment(e),
            filter(lambda e: e["kind"] == "FullComment", self.ast["inner"])
        ))[0]


class TranslationUnitDecl:
    def __init__(self, ast):
        self.ast = ast

    def functions(self):
        return list(map(
            lambda e: FunctionDecl(e),
            filter(lambda e: e["kind"] == "FunctionDecl", self.ast["inner"])
        ))


def read_ast_json(filename):
    f = open(filename, "r")
    ast = json.loads(f.read())
    f.close()
    return ast


translationUnit = TranslationUnitDecl(read_ast_json(sys.argv[1]))
functions = translationUnit.functions()
print(functions[0].name)
print(functions[0].params()[0].name)
print(functions[0].comment().comment_text())
print(functions[0].comment().comment_params()[0].comment_text())
print(functions[0].params()[0].size())
#
# functionDecl = functions[0]
# name = functionDecl.name
# mangledName = functionDecl["mangledName"]
#
# params = list(filter(lambda e: e["kind"] == "ParmVarDecl", functionDecl["inner"]))
# print("name: " + name)
# print("mangledName: " + mangledName)
