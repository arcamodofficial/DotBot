#ifndef ARCAMOD_ESP_VEHICLE_CONFIG_H
#define ARCAMOD_ESP_VEHICLE_CONFIG_H

#include "ESPDrawHelpers.h"

constexpr float VEHICLE_BOX_WIDTH = 120.0f;
constexpr float VEHICLE_BOX_HEIGHT = 60.0f;
constexpr float VEHICLE_LINE_THICKNESS = 1.0f;
constexpr float VEHICLE_BOX_THICKNESS = 1.0f;
constexpr float VEHICLE_MAX_DISTANCE = 1500.0f;
constexpr float VEHICLE_SCREEN_MARGIN = 50.0f;
constexpr float VEHICLE_POSITION_EPSILON = 0.1f;

constexpr float VEHICLE_LABEL_OFFSET = 20.0f;
constexpr float VEHICLE_DISTANCE_OFFSET = 45.0f;
constexpr float VEHICLE_HEALTH_OFFSET = 8.0f;
constexpr float VEHICLE_LINE_BOTTOM_MARGIN = 50.0f;
constexpr float VEHICLE_HEALTH_BAR_WIDTH = 6.0f;

constexpr ImU32 VEHICLE_LINE_COLOR = IM_COL32(255, 255, 0, 180);
constexpr ImU32 VEHICLE_BOX_COLOR = IM_COL32(255, 165, 0, 160);
constexpr ImU32 VEHICLE_DISTANCE_COLOR = IM_COL32(255, 255, 255, 200);
constexpr ImU32 VEHICLE_LABEL_COLOR = IM_COL32(255, 165, 0, 180);
constexpr ImU32 VEHICLE_TEXT_OUTLINE = IM_COL32(0, 0, 0, 120);
constexpr ImU32 VEHICLE_HEALTH_COLOR_FULL = IM_COL32(0, 255, 0, 200);
constexpr ImU32 VEHICLE_HEALTH_COLOR_LOW = IM_COL32(255, 0, 0, 200);

static inline bool IsValidVehicle(void* vehicle) {
    if (!isValidPtr(vehicle)) return false;

    if (IsVehicleBroken(vehicle)) return false;

    return true;
}

inline Vector3 GetVehicleWorldPosition(void* vehicle) {
    Vector3 position = {0, 0, 0};
    if (!IsValidVehicle(vehicle)) return position;

    void* transform = GetVehicleTransform(vehicle);
    if (isValidPtr(transform)) {
        Vector3 transformPos = Transform$$get_position(transform);

        if (VALIDATE_VALUE(transformPos.x) && VALIDATE_VALUE(transformPos.y) && VALIDATE_VALUE(transformPos.z)) {
            if (transformPos.x != 0.0f || transformPos.y != 0.0f || transformPos.z != 0.0f) {
                return transformPos;
            }
        }
    }

    Vector3 chassisPos = GetVehicleChassisPosition(vehicle);
    if (VALIDATE_VALUE(chassisPos.x) && VALIDATE_VALUE(chassisPos.y) && VALIDATE_VALUE(chassisPos.z)) {
        if (isValidPtr(transform)) {
            Vector3 transformPos = Transform$$get_position(transform);
            if (VALIDATE_VALUE(transformPos.x) && VALIDATE_VALUE(transformPos.y) && VALIDATE_VALUE(transformPos.z)) {
                position.x = transformPos.x + chassisPos.x;
                position.y = transformPos.y + chassisPos.y;
                position.z = transformPos.z + chassisPos.z;
                return position;
            }
        }
        return chassisPos;
    }

    return position;
}

static inline Vector3 GetVehicleScreenPosition(void* vehicle, void* camera) {
    Vector3 screenPos = {-1, -1, -1};
    if (!IsValidVehicle(vehicle) || !isValidPtr(camera)) return screenPos;

    Vector3 worldPos = GetVehicleWorldPosition(vehicle);
    if (worldPos.x == 0.0f && worldPos.y == 0.0f && worldPos.z == 0.0f) return screenPos;

    return Camera$$WorldToScreenPoint(camera, worldPos);
}

inline float GetVehicleDistance(void* vehicle, const Vector3& cameraPos) {
    if (!IsValidVehicle(vehicle)) return 0.0f;

    Vector3 vehiclePos = GetVehicleWorldPosition(vehicle);
    if (vehiclePos.x == 0.0f && vehiclePos.y == 0.0f && vehiclePos.z == 0.0f) return 0.0f;

    float dx = vehiclePos.x - cameraPos.x;
    float dy = vehiclePos.y - cameraPos.y;
    float dz = vehiclePos.z - cameraPos.z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

inline float GetVehicleHealthPercentage(void* vehicle) {
    if (!IsValidVehicle(vehicle)) return 0.0f;

    float health = GetVehicleHealth(vehicle);
    if (health <= 0.0f) return 0.0f;

    float maxHealth = GetVehicleMaxHealth(vehicle);
    if (maxHealth <= 0.0f) maxHealth = 100.0f;

    float percentage = health / maxHealth;
    return std::min(std::max(percentage, 0.0f), 1.0f);
}

static inline ImU32 GetVehicleHealthColor(float healthPercentage) {
    if (healthPercentage > 0.6f) {
        return VEHICLE_HEALTH_COLOR_FULL;
    } else if (healthPercentage > 0.3f) {
        float factor = (healthPercentage - 0.3f) / 0.3f;
        return IM_COL32(
                (int)(255 * (1.0f - factor)),
                255,
                0,
                200
        );
    } else {
        return VEHICLE_HEALTH_COLOR_LOW;
    }
}

static inline bool IsVehicleInScreenBounds(const Vector3& screenPos, float screenWidth, float screenHeight) {
    return screenPos.x >= -VEHICLE_SCREEN_MARGIN &&
           screenPos.x <= screenWidth + VEHICLE_SCREEN_MARGIN &&
           screenPos.y >= -VEHICLE_SCREEN_MARGIN &&
           screenPos.y <= screenHeight + VEHICLE_SCREEN_MARGIN &&
           screenPos.z > 0.0f;
}

inline void DrawVehicleLine(ImDrawList* draw, const Vector3& screenPos, float screenWidth, float screenHeight) {
    if (!Config.View.Vehicle.Line) return;

    ImVec2 bottomCenter(screenWidth * 0.5f, screenHeight - VEHICLE_LINE_BOTTOM_MARGIN);
    ImVec2 vehicleScreen(screenPos.x, screenHeight - screenPos.y);

    draw->AddLine(bottomCenter, vehicleScreen, VEHICLE_LINE_COLOR, VEHICLE_LINE_THICKNESS);
}

inline void DrawVehicleBox(ImDrawList* draw, const Vector3& screenPos, float screenWidth, float screenHeight) {
    if (!Config.View.Vehicle.Box) return;

    float boxX = screenPos.x - VEHICLE_BOX_WIDTH * 0.5f;
    float boxY = (screenHeight - screenPos.y) - VEHICLE_BOX_HEIGHT * 0.5f;

    ImVec2 boxMin(boxX, boxY);
    ImVec2 boxMax(boxX + VEHICLE_BOX_WIDTH, boxY + VEHICLE_BOX_HEIGHT);

    draw->AddRect(boxMin, boxMax, VEHICLE_BOX_COLOR, 0.0f, 0, VEHICLE_BOX_THICKNESS);
}

inline void DrawVehicleDistance(ImDrawList* draw, const Vector3& screenPos, float distance, float screenHeight) {
    if (!Config.View.Vehicle.Distance) return;

    static char distanceText[32];
    snprintf(distanceText, sizeof(distanceText), "%.0fm", distance);

    float boxTopY = (screenHeight - screenPos.y) - VEHICLE_BOX_HEIGHT * 0.5f;
    ImVec2 textPos(screenPos.x, boxTopY - VEHICLE_DISTANCE_OFFSET);

    ImVec2 textSize = ImGui::CalcTextSize(distanceText);
    textPos.x -= textSize.x * 0.5f;

    draw->AddText(ImVec2(textPos.x + 1, textPos.y + 1), VEHICLE_TEXT_OUTLINE, distanceText);
    draw->AddText(textPos, VEHICLE_DISTANCE_COLOR, distanceText);
}

inline void DrawVehicleHealth(ImDrawList* draw, const Vector3& screenPos, float healthPercentage, float screenHeight) {
    if (!Config.View.Vehicle.Health) return;

    float healthBarWidth = VEHICLE_HEALTH_BAR_WIDTH;
    float healthBarHeight = VEHICLE_BOX_HEIGHT;

    float boxRightX = screenPos.x + VEHICLE_BOX_WIDTH * 0.5f;
    float boxTopY = (screenHeight - screenPos.y) - VEHICLE_BOX_HEIGHT * 0.5f;

    float barX = boxRightX + VEHICLE_HEALTH_OFFSET;
    float barY = boxTopY;

    ImVec2 barMin(barX, barY);
    ImVec2 barMax(barX + healthBarWidth, barY + healthBarHeight);

    float healthHeight = healthBarHeight * healthPercentage;
    ImVec2 healthMin(barX, barY + healthBarHeight - healthHeight);
    ImVec2 healthMax(barX + healthBarWidth, barY + healthBarHeight);

    draw->AddRectFilled(barMin, barMax, IM_COL32(0, 0, 0, 120));

    if (healthPercentage > 0.0f) {
        ImU32 healthColor = GetVehicleHealthColor(healthPercentage);
        draw->AddRectFilled(healthMin, healthMax, healthColor);
    }

    draw->AddRect(barMin, barMax, IM_COL32(255, 255, 255, 150), 0.0f, 0, 0.8f);
}

inline void DrawVehicleLabel(ImDrawList* draw, const Vector3& screenPos, float screenHeight) {
    char vehicleLabel[8];
    vehicleLabel[0] = 'V'; vehicleLabel[1] = 'E'; vehicleLabel[2] = 'H'; vehicleLabel[3] = 'I';
    vehicleLabel[4] = 'C'; vehicleLabel[5] = 'L'; vehicleLabel[6] = 'E'; vehicleLabel[7] = '\0';

    float boxTopY = (screenHeight - screenPos.y) - VEHICLE_BOX_HEIGHT * 0.5f;
    ImVec2 textPos(screenPos.x, boxTopY - VEHICLE_LABEL_OFFSET);

    ImVec2 textSize = ImGui::CalcTextSize(vehicleLabel);
    textPos.x -= textSize.x * 0.5f;

    draw->AddText(ImVec2(textPos.x + 1, textPos.y + 1), VEHICLE_TEXT_OUTLINE, vehicleLabel);
    draw->AddText(textPos, VEHICLE_LABEL_COLOR, vehicleLabel);
}

#endif // ARCAMOD_ESP_VEHICLE_CONFIG_H