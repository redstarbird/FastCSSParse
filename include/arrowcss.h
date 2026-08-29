#ifndef ARROWCSS
#define ARROWCSS

#include <stdbool.h>
#include <StringPool.h>

// Configuration for the CSS generator
struct CSSGeneratorConfig
{
    // Whether to minify the generated CSS
    bool minify;
    // The number of spaces to use for indentation in the generated CSS
    unsigned int indentLevel;
    // Whether to use tabs for indentation instead of spaces
    bool useTabs;

    // Whether to generate source maps for the generated CSS
    bool generateSourceMap;

    // Name of the input file (defaults to "source.css" if empty)
    const char *inputFileName;

    // Name of the output source map if being generated (defaults to "out.css.map" if empty)
    const char *outputMapName;
};

/** @brief Structure representing the entire CSS Abstract Syntax Tree (AST) */
typedef struct CSSAST
{
    /** @brief Internal, read-only: String pool for managing string literals */
    struct StringPool *stringPool;
    /** @brief Internal, read-only: Memory arena for allocating AST nodes */
    struct MemoryArena *arena;
    /** @brief Read-only: Root node of the AST */
    struct ASTNode *root;
    /** @brief Internal, read-only: Tracks the ownership of the memory arena */
    bool ownsArena;
    /** @brief Internal, read-only: Tracks the ownership of the string pool */
    bool ownsStringPool;
} CSSAST;

/** Generates CSS from a CSS AST based on the provided configuration. */
struct ArrowCSSBuildResult *ArrowCSS_GenerateCSSFromAST(struct CSSAST *ast, struct CSSGeneratorConfig *config);

typedef struct ArrowCssParseOptions
{
    // For error reporting
    const char *filename;
    // Should source maps be generated
    bool generateSourceMap;
    // Supress any console warnings
    bool silent;

    // Memory arena
    struct MemoryArena *arena;
    // String pool
    struct StringPool *pool;

} ArrowCssParseOptions;

// Contains the generated CSS and source map (if requested)
typedef struct ArrowCSSBuildResult
{
    // The generated CSS string
    char *css;
    // The generated source map string (if requested)
    char *sourceMap;
} ArrowCSSBuildResult;

struct CSSAST *ParseCSSToAST(char *fileContent, size_t length, struct ArrowCssParseOptions *options);

/// @brief Frees the memory of the provided AST, this can only be done for the string pool and/or memory arena if they are not provided by the user.
/// @param ast The ast to be destroyed
void ArrowCSS_DestroyAST(struct CSSAST *ast);

#endif