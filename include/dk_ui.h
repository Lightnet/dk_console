//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#if !defined(DK_UI_H)
#define DK_UI_H

#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(RAYLIB_H)
#include "raylib.h"
#endif

#include <math.h>   // floorf, ceilf, roundf
#include <stdio.h>  // sprintf
#include <string.h> // strlen, strcpy, strcat

typedef struct ImUITheme
{
    Color background;
    Color text;
    Color button;
    Color buttonHover;
    Color buttonActive;
    Color toggle;
    Color toggleHover;
    Color toggleCursor;
    Color select;
    Color selectActive;
    Color slider;
    Color sliderCursor;
    Color sliderCursorHover;
    Color sliderCursorActive;
    Color property;
    Color border;
    Color textFiledCursor;
    Color textFiledSelection;
    Color optionText;
    Color optionBackground;
    Color optionHover;
} ImUITheme;

typedef struct ImUIStyle
{
    int borderSize;
    float roundness;
} ImUIStyle;

typedef struct ImUI
{
    Font* font;
    ImUITheme* theme;
    ImUIStyle* style;
} ImUI;

// Default style
static ImUIStyle DK_ImUIDefaultStyle = {
    .borderSize = 1,
    .roundness = 0.0f,
};

// Default theme (dark)
static ImUITheme DK_ImUIDefaultTheme = {
    .background = {50, 50, 50, 255},
    .text = {255, 255, 255, 255},
    .button = {50, 50, 50, 255},
    .buttonHover = {60, 60, 60, 255},
    .buttonActive = {60, 60, 60, 255},
    .toggle = {60, 60, 60, 255},
    .toggleHover = {70, 70, 70, 255},
    .toggleCursor = {80, 80, 80, 255},
    .select = {60, 60, 60, 255},
    .selectActive = {60, 60, 60, 255},
    .slider = {50, 50, 50, 255},
    .sliderCursor = {80, 80, 80, 255},
    .sliderCursorHover = {80, 80, 80, 255},
    .sliderCursorActive = {80, 80, 80, 255},
    .property = {50, 50, 50, 255},
    .border = {60, 60, 60, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {255, 255, 255, 255},
    .optionBackground = {50, 50, 50, 255},
    .optionHover = {60, 60, 60, 255},
};

// Solarized theme
static ImUITheme DK_ImUISolarizedTheme = {
    .background = {0, 43, 54, 255},
    .text = {131, 148, 150, 255},
    .button = {7, 54, 66, 255},
    .buttonHover = {88, 110, 117, 255},
    .buttonActive = {88, 110, 117, 255},
    .toggle = {7, 54, 66, 255},
    .toggleHover = {88, 110, 117, 255},
    .toggleCursor = {101, 123, 131, 255},
    .select = {7, 54, 66, 255},
    .selectActive = {88, 110, 117, 255},
    .slider = {7, 54, 66, 255},
    .sliderCursor = {101, 123, 131, 255},
    .sliderCursorHover = {88, 110, 117, 255},
    .sliderCursorActive = {101, 123, 131, 255},
    .property = {7, 54, 66, 255},
    .border = {101, 123, 131, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 0, 0, 100},
    .optionText = {131, 148, 150, 255},
    .optionBackground = {7, 54, 66, 255},
    .optionHover = {88, 110, 117, 255},
};

// Light theme
static ImUITheme DK_ImUILightTheme = {
    .background = {210, 210, 210, 255},
    .text = {50, 50, 50, 255},
    .button = {200, 200, 200, 255},
    .buttonHover = {175, 175, 175, 255},
    .buttonActive = {175, 175, 175, 255},
    .toggle = {200, 200, 200, 255},
    .toggleHover = {175, 175, 175, 255},
    .toggleCursor = {50, 50, 50, 255},
    .select = {200, 200, 200, 255},
    .selectActive = {175, 175, 175, 255},
    .slider = {200, 200, 200, 255},
    .sliderCursor = {50, 50, 50, 255},
    .sliderCursorHover = {50, 50, 50, 255},
    .sliderCursorActive = {50, 50, 50, 255},
    .property = {200, 200, 200, 255},
    .border = {175, 175, 175, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {200, 200, 200, 255},
    .optionBackground = {175, 175, 175, 255},
    .optionHover = {50, 50, 50, 255},
};

// Dark theme
static ImUITheme DK_ImUIDarkTheme = {
    .background = {45, 45, 45, 255},
    .text = {235, 235, 235, 255},
    .button = {60, 60, 60, 255},
    .buttonHover = {75, 75, 75, 255},
    .buttonActive = {75, 75, 75, 255},
    .toggle = {60, 60, 60, 255},
    .toggleHover = {75, 75, 75, 255},
    .toggleCursor = {175, 175, 175, 255},
    .select = {60, 60, 60, 255},
    .selectActive = {75, 75, 75, 255},
    .slider = {60, 60, 60, 255},
    .sliderCursor = {175, 175, 175, 255},
    .sliderCursorHover = {175, 175, 175, 255},
    .sliderCursorActive = {175, 175, 175, 255},
    .property = {60, 60, 60, 255},
    .border = {75, 75, 75, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {60, 60, 60, 255},
    .optionBackground = {75, 75, 75, 255},
    .optionHover = {175, 175, 175, 255},
};

// Monokai theme
static ImUITheme DK_ImUIMonokaiTheme = {
    .background = {39, 40, 34, 255},
    .text = {248, 248, 242, 255},
    .button = {50, 50, 50, 255},
    .buttonHover = {75, 75, 75, 255},
    .buttonActive = {75, 75, 75, 255},
    .toggle = {50, 50, 50, 255},
    .toggleHover = {75, 75, 75, 255},
    .toggleCursor = {175, 175, 175, 255},
    .select = {50, 50, 50, 255},
    .selectActive = {75, 75, 75, 255},
    .slider = {50, 50, 50, 255},
    .sliderCursor = {175, 175, 175, 255},
    .sliderCursorHover = {175, 175, 175, 255},
    .sliderCursorActive = {175, 175, 175, 255},
    .property = {50, 50, 50, 255},
    .border = {75, 75, 75, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {50, 50, 50, 255},
    .optionBackground = {75, 75, 75, 255},
    .optionHover = {175, 175, 175, 255},
};

// Nord theme
static ImUITheme DK_ImUINordTheme = {
    .background = {46, 52, 64, 255},
    .text = {229, 233, 240, 255},
    .button = {60, 56, 64, 255},
    .buttonHover = {75, 71, 79, 255},
    .buttonActive = {75, 71, 79, 255},
    .toggle = {60, 56, 64, 255},
    .toggleHover = {75, 71, 79, 255},
    .toggleCursor = {175, 175, 175, 255},
    .select = {60, 56, 64, 255},
    .selectActive = {75, 71, 79, 255},
    .slider = {60, 56, 64, 255},
    .sliderCursor = {175, 175, 175, 255},
    .sliderCursorHover = {175, 175, 175, 255},
    .sliderCursorActive = {175, 175, 175, 255},
    .property = {60, 56, 64, 255},
    .border = {75, 71, 79, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {60, 56, 64, 255},
    .optionBackground = {75, 71, 79, 255},
    .optionHover = {175, 175, 175, 255},
};

// White theme
static ImUITheme DK_ImUIWhiteTheme = {
    .background = {255, 255, 255, 255},
    .text = {50, 50, 50, 255},
    .button = {200, 200, 200, 255},
    .buttonHover = {175, 175, 175, 255},
    .buttonActive = {175, 175, 175, 255},
    .toggle = {200, 200, 200, 255},
    .toggleHover = {175, 175, 175, 255},
    .toggleCursor = {50, 50, 50, 255},
    .select = {200, 200, 200, 255},
    .selectActive = {175, 175, 175, 255},
    .slider = {200, 200, 200, 255},
    .sliderCursor = {50, 50, 50, 255},
    .sliderCursorHover = {50, 50, 50, 255},
    .sliderCursorActive = {50, 50, 50, 255},
    .property = {200, 200, 200, 255},
    .border = {175, 175, 175, 255},
    .textFiledCursor = {0, 228, 48, 255},
    .textFiledSelection = {0, 117, 44, 255},
    .optionText = {200, 200, 200, 255},
    .optionBackground = {175, 175, 175, 255},
    .optionHover = {50, 50, 50, 255},
};

// API function declarations
void DK_DrawColorPicker(ImUI* io, Vector2 pos, Color* result, bool* is_open);
void DK_DrawSlider(ImUI* io, Vector2 position, float width, float height, float* value, float min, float max, float step, bool* focused);
int DK_DrawButton(ImUI* io, Vector2 position, float width, float height, const char* text);
int DK_DrawDropdown(ImUI* io, Vector2 position, float width, float height, const char* text, char** options, size_t el_size, int* selected, bool* is_open);
const char* DK_DrawInputField(ImUI* io, Vector2 position, float width, float height, char* text, bool* focused, void (*callback)(const char*));

#if defined(__cplusplus)
}
#endif

#endif // DK_UI_H