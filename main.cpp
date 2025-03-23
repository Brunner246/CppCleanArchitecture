#include <iostream>

/*
*The Visitor pattern is more appropriate here than the Strategy pattern because:

1. **Multiple operations on fixed structure**: Visitor excels when you have different operations (JSON export, serialization)
that need to be performed on a fixed class hierarchy (Document).

2. **Double dispatch mechanism**: Visitor allows for "double dispatch" where both the visitor type and concrete
document type determine the behavior, while Strategy only varies the algorithm.

3. **Extensibility**: Adding new export formats (new visitors) doesn't require changing existing Document classes.
With Strategy, you'd need to modify the Document class each time.

4. **Separation of concerns**: Visitor completely separates the operation implementation from the Document class hierarchy.

Strategy would be more appropriate if you were selecting different algorithms for a single operation, rather than
implementing completely different operations like export and serialization.
*/

class ByteStream {
};

class Document {
public:
    virtual ~Document() = default;

    // Accept a visitor instead of having format-specific methods
    virtual void accept(class DocumentVisitor &visitor) const = 0;

    // Document core functionality methods go here...
};

// DocumentVisitor.hpp
class DocumentVisitor {
public:
    virtual ~DocumentVisitor() = default;

    virtual void visit(const Document &document) = 0;
};

// JSONExporter.hpp
class JSONExporter : public DocumentVisitor {
public:
    void visit(const Document &document) override {
        // Implementation for JSON export
    }

    // Methods to retrieve the exported JSON
};

// Serializer.hpp
class Serializer : public DocumentVisitor {
public:
    explicit Serializer(ByteStream &stream) : stream_(stream) {
    }

    void visit(const Document &document) override {
        // Implementation for serialization to ByteStream
    }

private:
    ByteStream &stream_;
};

int execute() {
    Document *doc = /* get document */ nullptr;

    // For JSON export:
    JSONExporter jsonExporter;
    doc->accept(jsonExporter);

    // For serialization:
    ByteStream stream;
    Serializer serializer(stream);
    doc->accept(serializer);
}

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
