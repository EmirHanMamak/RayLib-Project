#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
worldPos(pos),
texture(tex) 
{
}
void Prop::Render(Vector2 knightPos) {
    Vector2 screenPos {Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}
Rectangle Prop::GetCollisionRec(Vector2 knightPos) {
    Vector2 screenPos {Vector2Subtract(worldPos, knightPos)};
    return Rectangle {
        screenPos.x + 10,
        screenPos.y + 10,
        texture.width * scale -30,
        texture.height * scale -30
    };
}

