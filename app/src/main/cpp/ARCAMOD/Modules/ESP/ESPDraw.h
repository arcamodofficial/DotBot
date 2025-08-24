#include "ESPDrawHelpers.h"
#include "ESPVehicleConfig.h"
#include <csignal>
#include <stdexcept>
#include <exception>

extern bool IsAnyESPFeatureActive();

static bool IsInActiveGame() {
    if (!Config.Init.IL2CppReady) {
        return false;
    }

    void *matchGame = GamePlay$$get_MatchGame();
    if (!matchGame) {
        return false;
    }

    unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)matchGame + Offsets::BaseGame::MatchInProgress);
    if (!matchInProgressPtr) {
        return false;
    }

    return (*matchInProgressPtr != 0);
}

void *DrawESP(ImDrawList *draw) noexcept {
    static sighandler_t original_SIGSEGV = nullptr;
    static sighandler_t original_SIGABRT = nullptr;

    original_SIGSEGV = signal(SIGSEGV, [](int) { return; });
    original_SIGABRT = signal(SIGABRT, [](int) { return; });
        if (!IsAnyESPFeatureActive()) {
            return nullptr;
        }

        if (!draw) {
            return nullptr;
        }

        if (!IsInActiveGame()) {
            return nullptr;
        }

        void *currentMatchGame = GamePlay$$get_MatchGame();
        if (!currentMatchGame) {
            return nullptr;
        }

        void *currentCamera = Camera$$get_main();
        if (!currentCamera) {
            return nullptr;
        }

        void *enemyListPtr = (void*)(*(uintptr_t*)((uintptr_t)currentMatchGame + Offsets::BaseGame::EnemyPawns));
        if (!enemyListPtr) {
            return nullptr;
        }

        List<void*> *enemyList = (List<void*>*)enemyListPtr;
        int enemyCount = enemyList->getSize();
        if (enemyCount <= 0 || enemyCount > 200) return nullptr;

        void **enemyItems = enemyList->getItems();
        if (!enemyItems) return nullptr;

        int maxEnemies = Config.View.Vehicle.Enable ? 35 : 50;
        for (int i = 0; i < enemyCount && i < maxEnemies; i++) {
            void *currentEnemy = enemyItems[i];
            if (!currentEnemy) continue;

            bool isAlive = *(bool*)((uintptr_t)currentEnemy + Offsets::Pawn::IsAlive);
            if (!isAlive) continue;

            void *headTransform = Pawn$$GetHeadTransform(currentEnemy);
            void *rootTransform = Pawn$$GetRootTransform(currentEnemy);
            if (!headTransform || !rootTransform) continue;

            Vector3 headPos = Transform$$get_position(headTransform);
            Vector3 rootPos = Transform$$get_position(rootTransform);

            if (!VALIDATE_VALUE(headPos.x) || !VALIDATE_VALUE(headPos.y) || !VALIDATE_VALUE(headPos.z) ||
                !VALIDATE_VALUE(rootPos.x) || !VALIDATE_VALUE(rootPos.y) || !VALIDATE_VALUE(rootPos.z)) {
                continue;
            }

            Vector3 headScreen = Camera$$WorldToScreenPoint(currentCamera, headPos);
            Vector3 rootScreen = Camera$$WorldToScreenPoint(currentCamera, rootPos);

            if (headScreen.z < 0 || rootScreen.z < 0) continue;
            if (headScreen.x < 0 || headScreen.x > glWidth ||
                headScreen.y < 0 || headScreen.y > glHeight) continue;

            bool isBot = *(bool*)((uintptr_t)currentEnemy + Offsets::Pawn::IsBot);
            void *playerInfo = GetPawnPlayerInfo(currentEnemy);

            if (Config.View.Box) {
                constexpr float BOX_HEIGHT_MULTIPLIER = 1.2f;
                constexpr float BOX_WIDTH_RATIO = 0.6f;
                constexpr float HEAD_OFFSET_RATIO = 0.1f;
                constexpr float CORNER_RATIO = 0.2f;
                constexpr float VERTICAL_CORNER_RATIO = 0.3f;
                constexpr float DEFAULT_THICKNESS = 2.0f;

                if (!(headScreen.x < -100 || headScreen.x > glWidth + 100 ||
                      headScreen.y < -100 || headScreen.y > glHeight + 100)) {

                    float actualHeight = std::abs(headScreen.y - rootScreen.y);
                    float boxHeight = actualHeight * BOX_HEIGHT_MULTIPLIER;
                    float boxWidth = boxHeight * BOX_WIDTH_RATIO;

                    float centerX = (headScreen.x + rootScreen.x) * 0.5f;
                    float headOffsetY = actualHeight * HEAD_OFFSET_RATIO;

                    const float left = centerX - (boxWidth * 0.5f);
                    const float top = glHeight - (headScreen.y + headOffsetY);
                    const float right = centerX + (boxWidth * 0.5f);
                    const float bottom = top + boxHeight;

                    ImColor baseColor = isBot ? ImColor(0, 255, 0, 180) : ImColor(255, 0, 0, 180);
                    ImColor glowColor = isBot ? ImColor(0, 255, 0, 60) : ImColor(255, 0, 0, 60);
                    ImColor highlightColor = isBot ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255);

                    if (Config.View.EnableBoxFill && !Config.View.DisableBoxFill) {
                        ImColor fillColor = isBot ? ImColor(50, 255, 50, 120) : ImColor(255, 50, 50, 120);
                        draw->AddRectFilled(ImVec2(left, top), ImVec2(right, bottom), fillColor);
                    }

                    if (!Config.View.EnableBoxFill || Config.View.DisableBoxFill) {
                        draw->AddRectFilled(ImVec2(left + 1, top + 1), ImVec2(right - 1, bottom - 1),
                                            ImColor(255, 255, 255, 12));
                    }

                    const float cornerH = boxWidth * CORNER_RATIO;
                    const float cornerV = boxHeight * VERTICAL_CORNER_RATIO;
                    const float glassThickness = 2.5f;

                    draw->AddLine(ImVec2(left - 1, top - 1), ImVec2(left + cornerH + 1, top - 1), glowColor, glassThickness + 1);
                    draw->AddLine(ImVec2(left - 1, top - 1), ImVec2(left - 1, top + cornerV + 1), glowColor, glassThickness + 1);

                    draw->AddLine(ImVec2(right - cornerH - 1, top - 1), ImVec2(right + 1, top - 1), glowColor, glassThickness + 1);
                    draw->AddLine(ImVec2(right + 1, top - 1), ImVec2(right + 1, top + cornerV + 1), glowColor, glassThickness + 1);

                    draw->AddLine(ImVec2(left - 1, bottom - cornerV - 1), ImVec2(left - 1, bottom + 1), glowColor, glassThickness + 1);
                    draw->AddLine(ImVec2(left - 1, bottom + 1), ImVec2(left + cornerH + 1, bottom + 1), glowColor, glassThickness + 1);

                    draw->AddLine(ImVec2(right + 1, bottom - cornerV - 1), ImVec2(right + 1, bottom + 1), glowColor, glassThickness + 1);
                    draw->AddLine(ImVec2(right - cornerH - 1, bottom + 1), ImVec2(right + 1, bottom + 1), glowColor, glassThickness + 1);

                    draw->AddLine(ImVec2(left, top), ImVec2(left + cornerH, top), baseColor, glassThickness);
                    draw->AddLine(ImVec2(left, top), ImVec2(left, top + cornerV), baseColor, glassThickness);

                    draw->AddLine(ImVec2(right - cornerH, top), ImVec2(right, top), baseColor, glassThickness);
                    draw->AddLine(ImVec2(right, top), ImVec2(right, top + cornerV), baseColor, glassThickness);

                    draw->AddLine(ImVec2(left, bottom - cornerV), ImVec2(left, bottom), baseColor, glassThickness);
                    draw->AddLine(ImVec2(left, bottom), ImVec2(left + cornerH, bottom), baseColor, glassThickness);

                    draw->AddLine(ImVec2(right, bottom - cornerV), ImVec2(right, bottom), baseColor, glassThickness);
                    draw->AddLine(ImVec2(right - cornerH, bottom), ImVec2(right, bottom), baseColor, glassThickness);

                    draw->AddLine(ImVec2(left, top), ImVec2(left + cornerH * 0.6f, top), highlightColor, 1.0f);
                    draw->AddLine(ImVec2(right - cornerH * 0.6f, top), ImVec2(right, top), highlightColor, 1.0f);
                }
            }

            if (Config.View.Line) {
                ImColor lineBaseColor = isBot ? ImColor(0, 255, 0, 200) : ImColor(255, 0, 0, 200);
                ImColor lineGlowColor = isBot ? ImColor(0, 255, 0, 80) : ImColor(255, 0, 0, 80);
                ImColor lineHighlight = isBot ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255);

                draw->AddLine(ImVec2(glWidth / 2, 0), ImVec2(headScreen.x, glHeight - headScreen.y),
                              lineGlowColor, 4.0f);

                draw->AddLine(ImVec2(glWidth / 2, 0), ImVec2(headScreen.x, glHeight - headScreen.y),
                              lineBaseColor, 2.5f);

                draw->AddLine(ImVec2(glWidth / 2, 0), ImVec2(headScreen.x, glHeight - headScreen.y),
                              lineHighlight, 1.0f);
            }

            float healthBarWidth = 160.0f;
            float leftEdge = headScreen.x - (healthBarWidth / 2);
            float rightEdge = headScreen.x + (healthBarWidth / 2);
            float topY = glHeight - headScreen.y - 35;

            float boxHeight = 18.0f;
            float boxTop = topY - 2.0f;
            float boxBottom = topY + boxHeight - 2.0f;

            float cutoutWidth = 40.0f;
            float cutoutLeft = rightEdge - cutoutWidth;
            float slopeOffset = 10.0f;

            if (Config.View.Name && playerInfo) {
                const char *playerName = GetPlayerNameDirect(currentEnemy);
                if (playerName) {
                    int teamID = *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::TeamID);

                    static char shortName[12];
                    if (strlen(playerName) > 6) {
                        strncpy(shortName, playerName, 6);
                        shortName[6] = '\0';
                        strcat(shortName, OBF("...."));
                    } else {
                        strcpy(shortName, playerName);
                    }

                    ImVec2 glowPoints[4] = {
                            ImVec2(leftEdge - 2, boxTop - 1),
                            ImVec2(cutoutLeft + slopeOffset + 2, boxTop - 1),
                            ImVec2(cutoutLeft - slopeOffset + 2, boxBottom + 1),
                            ImVec2(leftEdge - 2, boxBottom + 1)
                    };
                    draw->AddConvexPolyFilled(glowPoints, 4, ImColor(0, 0, 0, 60));

                    ImVec2 nameAreaPoints[4] = {
                            ImVec2(leftEdge, boxTop),
                            ImVec2(cutoutLeft + slopeOffset, boxTop),
                            ImVec2(cutoutLeft - slopeOffset, boxBottom),
                            ImVec2(leftEdge, boxBottom)
                    };
                    draw->AddConvexPolyFilled(nameAreaPoints, 4, ImColor(0, 0, 0, 120));

                    ImVec2 highlightPoints[4] = {
                            ImVec2(leftEdge, boxTop),
                            ImVec2(cutoutLeft + slopeOffset, boxTop),
                            ImVec2(cutoutLeft + slopeOffset - 1, boxTop + 1),
                            ImVec2(leftEdge, boxTop + 1)
                    };
                    draw->AddConvexPolyFilled(highlightPoints, 4, ImColor(255, 255, 255, 120));

                    draw->AddConvexPolyFilled(nameAreaPoints, 4, ImColor(255, 255, 255, 25));

                    ImVec2 distanceBorderPoints[4] = {
                            ImVec2(cutoutLeft + slopeOffset, boxTop),
                            ImVec2(rightEdge, boxTop),
                            ImVec2(rightEdge, boxBottom),
                            ImVec2(cutoutLeft - slopeOffset, boxBottom)
                    };

                    for (int i = 0; i < 4; i++) {
                        ImVec2 p1 = distanceBorderPoints[i];
                        ImVec2 p2 = distanceBorderPoints[(i + 1) % 4];
                        draw->AddLine(p1, p2, ImColor(255, 255, 255, 60), 0.8f);
                    }

                    ImColor teamColor;
                    switch (teamID % 8) {
                        case 0: teamColor = ImColor(255, 0, 0, 255); break;
                        case 1: teamColor = ImColor(0, 255, 0, 255); break;
                        case 2: teamColor = ImColor(0, 0, 255, 255); break;
                        case 3: teamColor = ImColor(255, 255, 0, 255); break;
                        case 4: teamColor = ImColor(255, 0, 255, 255); break;
                        case 5: teamColor = ImColor(0, 255, 255, 255); break;
                        case 6: teamColor = ImColor(255, 165, 0, 255); break;
                        case 7: teamColor = ImColor(128, 0, 128, 255); break;
                        default: teamColor = ImColor(255, 255, 255, 255); break;
                    }

                    float triangleSize = 12.0f;
                    ImVec2 p1(leftEdge, boxTop);
                    ImVec2 p2(leftEdge + triangleSize, boxTop);
                    ImVec2 p3(leftEdge, boxTop + triangleSize);

                    draw->AddTriangleFilled(ImVec2(p1.x - 1, p1.y - 1),
                                            ImVec2(p2.x + 1, p2.y - 1),
                                            ImVec2(p3.x - 1, p3.y + 1),
                                            ImColor(0, 0, 0, 120));

                    draw->AddTriangleFilled(p1, p2, p3, teamColor);

                    ImColor textColor = ImColor(255, 255, 255, 255);

                    draw->AddText(nullptr, 13.0f, ImVec2(leftEdge + triangleSize + 3, topY + 2), textColor, shortName);
                }
            }

            if (Config.View.Distance) {
                static float lastDistance = 0.0f;
                static void *lastDistanceEntity = nullptr;
                static Vector3 lastCameraPos = {0, 0, 0};

                float distance = 0.0f;

                if (lastDistanceEntity == currentEnemy) {
                    distance = lastDistance;
                } else {
                    Vector3 cameraPos = {0, 0, 0};
                    void *cameraTransform = Component$$get_transform(currentCamera);
                    if (cameraTransform) {
                        cameraPos = Transform$$get_position(cameraTransform);
                    }

                    float dx = headPos.x - cameraPos.x;
                    float dy = headPos.y - cameraPos.y;
                    float dz = headPos.z - cameraPos.z;
                    distance = sqrt(dx * dx + dy * dy + dz * dz);

                    lastDistance = distance;
                    lastDistanceEntity = currentEnemy;
                    lastCameraPos = cameraPos;
                }

                static char distanceText[8];
                static float lastTextDistance = -1.0f;
                if (abs(distance - lastTextDistance) > 2.0f) {
                    snprintf(distanceText, sizeof(distanceText), OBF("%.0fM"), distance);
                    lastTextDistance = distance;
                }

                ImColor distanceColor;
                if (distance > 100.0f) {
                    distanceColor = ImColor(255, 255, 255, 255);
                } else if (distance > 50.0f) {
                    float ratio = (distance - 50.0f) / 50.0f;
                    int red = 255;
                    int green = 255;
                    int blue = (int)(255 * ratio);
                    distanceColor = ImColor(red, green, blue, 255);
                } else if (distance > 20.0f) {
                    float ratio = (distance - 20.0f) / 30.0f;
                    int red = 255;
                    int green = (int)(255 * ratio);
                    int blue = 0;
                    distanceColor = ImColor(red, green, blue, 255);
                } else {
                    distanceColor = ImColor(255, 0, 0, 255);
                }

                if (!Config.View.Name) {
                    ImVec2 distanceGlowPoints[4] = {
                            ImVec2(cutoutLeft - slopeOffset - 2, boxTop - 1),
                            ImVec2(rightEdge + 2, boxTop - 1),
                            ImVec2(rightEdge + 2, boxBottom + 1),
                            ImVec2(cutoutLeft + slopeOffset - 2, boxBottom + 1)
                    };
                    draw->AddConvexPolyFilled(distanceGlowPoints, 4, ImColor(0, 0, 0, 60));

                    ImVec2 distanceBoxPoints[4] = {
                            ImVec2(cutoutLeft - slopeOffset, boxTop),
                            ImVec2(rightEdge, boxTop),
                            ImVec2(rightEdge, boxBottom),
                            ImVec2(cutoutLeft + slopeOffset, boxBottom)
                    };
                    draw->AddConvexPolyFilled(distanceBoxPoints, 4, ImColor(0, 0, 0, 180)); // Glass black
                }

                draw->AddText(nullptr, 13.0f, ImVec2(rightEdge - 30, topY + 2), distanceColor, distanceText);
            }

            if (Config.View.DetailedTeamInfo && playerInfo) {
                int playerKills = GetPlayerKillCount(playerInfo);
                int playerDeaths = GetPlayerDeathCount(playerInfo);
                int playerAssists = GetPlayerAssistCount(playerInfo);
                int playerDamage = GetPlayerTotalDamage(playerInfo);
                bool playerIsFiring = IsPlayerFiring(playerInfo);

                bool playerIsSkiing = false;
                if (currentEnemy) {
                    int skiingValue = *(int*)((uintptr_t)currentEnemy + Offsets::Pawn::IsSkiing);
                    playerIsSkiing = (skiingValue | 1) == 29;
                }

                float healthBarWidth = 160.0f;
                float leftEdge = headScreen.x - (healthBarWidth / 2);
                float rightEdge = headScreen.x + (healthBarWidth / 2);
                float bottomY = glHeight - rootScreen.y + 25;

                ImColor statsColor = ImColor(255, 255, 255, 255);

                static char deathText[8], killText[8], assistText[8], damageText[12];
                snprintf(deathText, sizeof(deathText), OBF("%d"), playerDeaths);
                snprintf(killText, sizeof(killText), OBF("%d"), playerKills);
                snprintf(assistText, sizeof(assistText), OBF("%d"), playerAssists);
                snprintf(damageText, sizeof(damageText), OBF("%d"), playerDamage);

                float fontSize = 15.0f;
                float spacing = 90.0f;
                float rightShift = 3.0f;

                static char labeledDeathText[20], labeledKillText[20], labeledAssistText[20], labeledDamageText[24];
                snprintf(labeledDeathText, sizeof(labeledDeathText), OBF("Death : %d"), playerDeaths);
                snprintf(labeledKillText, sizeof(labeledKillText), OBF("Kill : %d"), playerKills);
                snprintf(labeledAssistText, sizeof(labeledAssistText), OBF("Assist : %d"), playerAssists);
                snprintf(labeledDamageText, sizeof(labeledDamageText), OBF("DMG : %d"), playerDamage);

                draw->AddText(nullptr, fontSize, ImVec2(leftEdge - 65.0f, bottomY), statsColor, labeledDamageText);
                draw->AddText(nullptr, fontSize, ImVec2(leftEdge + 20.0f, bottomY), statsColor, labeledKillText);
                draw->AddText(nullptr, fontSize, ImVec2(leftEdge + 95.0f, bottomY), statsColor, labeledAssistText);
                draw->AddText(nullptr, fontSize, ImVec2(leftEdge + 165.0f, bottomY), statsColor, labeledDeathText);

                if (playerIsFiring) {
                    float glassBoxY = glHeight - headScreen.y - 30;
                    float indicatorX = headScreen.x + (healthBarWidth / 2) + 10;

                    float time = ImGui::GetTime();
                    float alpha = (sinf(time * 10.0f) * 0.5f + 0.5f);

                    ImColor firingColor = ImColor(255, 0, 0, (int)(255 * alpha));
                    ImColor firingColorOuter = ImColor(255, 100, 0, (int)(155 * alpha));

                    float triangleSize = 8.0f;
                    ImVec2 trianglePoints[3] = {
                            ImVec2(indicatorX, glassBoxY - triangleSize),
                            ImVec2(indicatorX + triangleSize, glassBoxY + triangleSize/2),
                            ImVec2(indicatorX - triangleSize, glassBoxY + triangleSize/2)
                    };
                    draw->AddTriangleFilled(trianglePoints[0], trianglePoints[1], trianglePoints[2], firingColorOuter);
                    draw->AddCircleFilled(ImVec2(indicatorX, glassBoxY), 3.0f, firingColor);

                    ImColor firingTextColor = ImColor(255, 0, 0, 255);
                    ImColor shadowColor = ImColor(0, 0, 0, 180);
                    float textX = indicatorX + triangleSize + 5.0f;
                    float textY = glassBoxY - 8.0f;

                    draw->AddText(nullptr, 16.0f, ImVec2(textX + 1, textY + 1), shadowColor, OBF("FIRING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX - 1, textY - 1), shadowColor, OBF("FIRING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX + 1, textY - 1), shadowColor, OBF("FIRING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX - 1, textY + 1), shadowColor, OBF("FIRING"));

                    draw->AddText(nullptr, 16.0f, ImVec2(textX, textY), firingTextColor, OBF("FIRING"));

                } else if (playerIsSkiing) {
                    float glassBoxY = glHeight - headScreen.y - 30;
                    float indicatorX = headScreen.x + (healthBarWidth / 2) + 10;

                    float time = ImGui::GetTime();
                    float alpha = (sinf(time * 10.0f) * 0.5f + 0.5f);

                    ImColor skiingColor = ImColor(0, 191, 255, (int)(255 * alpha));
                    ImColor skiingColorOuter = ImColor(0, 120, 215, (int)(155 * alpha));

                    float triangleSize = 8.0f;
                    ImVec2 trianglePoints[3] = {
                            ImVec2(indicatorX, glassBoxY - triangleSize),
                            ImVec2(indicatorX + triangleSize, glassBoxY + triangleSize/2),
                            ImVec2(indicatorX - triangleSize, glassBoxY + triangleSize/2)
                    };
                    draw->AddTriangleFilled(trianglePoints[0], trianglePoints[1], trianglePoints[2], skiingColorOuter);
                    draw->AddCircleFilled(ImVec2(indicatorX, glassBoxY), 3.0f, skiingColor);

                    ImColor skiingTextColor = ImColor(0, 191, 255, 255);
                    ImColor shadowColor = ImColor(0, 0, 0, 180);
                    float textX = indicatorX + triangleSize + 5.0f;
                    float textY = glassBoxY - 8.0f;

                    draw->AddText(nullptr, 16.0f, ImVec2(textX + 1, textY + 1), shadowColor, OBF("SKIING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX - 1, textY - 1), shadowColor, OBF("SKIING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX + 1, textY - 1), shadowColor, OBF("SKIING"));
                    draw->AddText(nullptr, 16.0f, ImVec2(textX - 1, textY + 1), shadowColor, OBF("SKIING"));

                    draw->AddText(nullptr, 16.0f, ImVec2(textX, textY), skiingTextColor, OBF("SKIING"));
                }
            }

            if (Config.View.Health && playerInfo) {
                float currentHealth = GetPlayerHealth(playerInfo);
                float maxHealth = GetPlayerMaxHealth(playerInfo);

                if (maxHealth <= 0) maxHealth = 100.0f;
                float healthPercent = currentHealth / maxHealth;
                if (healthPercent > 1.0f) healthPercent = 1.0f;
                if (healthPercent < 0.0f) healthPercent = 0.0f;

                float barWidth = 160.0f;
                float barHeight = 6.0f;
                float barX = headScreen.x - (barWidth / 2);
                float barY = glHeight - headScreen.y - 15;

                draw->AddRectFilled(ImVec2(barX - 1, barY - 1), ImVec2(barX + barWidth + 1, barY + barHeight + 1),
                                    ImColor(0, 0, 0, 120));

                draw->AddRectFilled(ImVec2(barX, barY), ImVec2(barX + barWidth, barY + barHeight),
                                    ImColor(50, 50, 50, 180));

                ImColor healthBaseColor = (healthPercent > 0.7f) ? ImColor(255, 255, 255, 150) :
                                          (healthPercent > 0.3f) ? ImColor(255, 255, 0, 150) :
                                          ImColor(255, 0, 0, 150);

                ImColor healthGlowColor = (healthPercent > 0.7f) ? ImColor(255, 255, 255, 60) :
                                          (healthPercent > 0.3f) ? ImColor(255, 255, 0, 60) :
                                          ImColor(255, 0, 0, 60);

                ImColor healthHighlight = (healthPercent > 0.7f) ? ImColor(255, 255, 255, 200) :
                                          (healthPercent > 0.3f) ? ImColor(255, 255, 0, 200) :
                                          ImColor(255, 0, 0, 200);

                float healthWidth = barWidth * healthPercent;

                draw->AddRectFilled(ImVec2(barX - 1, barY - 1),
                                    ImVec2(barX + healthWidth + 1, barY + barHeight + 1),
                                    healthGlowColor);

                draw->AddRectFilled(ImVec2(barX, barY),
                                    ImVec2(barX + healthWidth, barY + barHeight),
                                    healthBaseColor);

                if (healthWidth > 2) {
                    draw->AddRectFilled(ImVec2(barX, barY),
                                        ImVec2(barX + healthWidth, barY + 1),
                                        healthHighlight);
                }

                draw->AddRectFilled(ImVec2(barX, barY),
                                    ImVec2(barX + healthWidth, barY + barHeight),
                                    ImColor(255, 255, 255, 25));
            }

            if (Config.View.Skeleton) {
                void *headBone = (void*)(*(uintptr_t*)((uintptr_t)currentEnemy + Offsets::Pawn::HeadBone));
                void *neckBone = (void*)(*(uintptr_t*)((uintptr_t)currentEnemy + Offsets::Pawn::NeckBone));
                void *hipsBone = (void*)(*(uintptr_t*)((uintptr_t)currentEnemy + Offsets::Pawn::HipsBone));
                void *leftAnkleBone = (void*)(*(uintptr_t*)((uintptr_t)currentEnemy + Offsets::Pawn::LeftAnkleBone));
                void *rightAnkleBone = (void*)(*(uintptr_t*)((uintptr_t)currentEnemy + Offsets::Pawn::RightAnkleBone));

                if (headBone && neckBone && hipsBone) {
                    Vector3 headPos = Transform$$get_position(headBone);
                    Vector3 neckPos = Transform$$get_position(neckBone);
                    Vector3 hipsPos = Transform$$get_position(hipsBone);

                    if (VALIDATE_VALUE(headPos.x) && VALIDATE_VALUE(headPos.y) && VALIDATE_VALUE(headPos.z) &&
                        VALIDATE_VALUE(neckPos.x) && VALIDATE_VALUE(neckPos.y) && VALIDATE_VALUE(neckPos.z) &&
                        VALIDATE_VALUE(hipsPos.x) && VALIDATE_VALUE(hipsPos.y) && VALIDATE_VALUE(hipsPos.z)) {

                        Vector3 headScreen = Camera$$WorldToScreenPoint(currentCamera, headPos);
                        Vector3 neckScreen = Camera$$WorldToScreenPoint(currentCamera, neckPos);
                        Vector3 hipsScreen = Camera$$WorldToScreenPoint(currentCamera, hipsPos);

                        if (headScreen.z > 0 && neckScreen.z > 0 && hipsScreen.z > 0) {
                            ImColor skeletonColor = isBot ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255);

                            draw->AddLine(ImVec2(headScreen.x, glHeight - headScreen.y),
                                          ImVec2(neckScreen.x, glHeight - neckScreen.y), skeletonColor, 2.0f);

                            draw->AddLine(ImVec2(neckScreen.x, glHeight - neckScreen.y),
                                          ImVec2(hipsScreen.x, glHeight - hipsScreen.y), skeletonColor, 2.0f);

                            if (leftAnkleBone && rightAnkleBone) {
                                Vector3 leftAnklePos = Transform$$get_position(leftAnkleBone);
                                Vector3 rightAnklePos = Transform$$get_position(rightAnkleBone);

                                if (VALIDATE_VALUE(leftAnklePos.x) && VALIDATE_VALUE(leftAnklePos.y) && VALIDATE_VALUE(leftAnklePos.z) &&
                                    VALIDATE_VALUE(rightAnklePos.x) && VALIDATE_VALUE(rightAnklePos.y) && VALIDATE_VALUE(rightAnklePos.z)) {

                                    Vector3 leftAnkleScreen = Camera$$WorldToScreenPoint(currentCamera, leftAnklePos);
                                    Vector3 rightAnkleScreen = Camera$$WorldToScreenPoint(currentCamera, rightAnklePos);

                                    if (leftAnkleScreen.z > 0 && rightAnkleScreen.z > 0) {
                                        draw->AddLine(ImVec2(hipsScreen.x, glHeight - hipsScreen.y),
                                                      ImVec2(leftAnkleScreen.x, glHeight - leftAnkleScreen.y), skeletonColor, 2.0f);

                                        draw->AddLine(ImVec2(hipsScreen.x, glHeight - hipsScreen.y),
                                                      ImVec2(rightAnkleScreen.x, glHeight - rightAnkleScreen.y), skeletonColor, 2.0f);
                                    }
                                }
                            }
                        }
                    }
                }
            }


        }

        void* cameraTransform = Component$$get_transform(currentCamera);
        Vector3 cameraPos = {0, 0, 0};
        if (cameraTransform) {
            cameraPos = Transform$$get_position(cameraTransform);
        }

        if (Config.View.Vehicle.Enable) {
            void* allVehiclesPtr = GetAllVehicles(currentMatchGame);

            if (!allVehiclesPtr) {
                void* vehicleManager = *(void**)((uintptr_t)currentMatchGame + Offsets::Vehicle::VehicleMgr);
                if (vehicleManager) {
                    allVehiclesPtr = *(void**)((uintptr_t)vehicleManager + Offsets::Vehicle::AvailableVehicles);
                }
            }

            if (allVehiclesPtr) {
                List<void*>* vehicleList = (List<void*>*)allVehiclesPtr;
                int vehicleCount = vehicleList->getSize();

#if IS_DEV
                // LOGI("ARCA", "Vehicle ESP: Found %d vehicles", vehicleCount);
#endif

                int maxVehicles = (enemyCount > 30) ? 20 : 30;
                if (vehicleCount > 0 && vehicleCount <= maxVehicles) {
                    void** vehicleItems = vehicleList->getItems();
                    if (vehicleItems) {

                        for (int v = 0; v < vehicleCount; v++) {
                            void* currentVehicle = vehicleItems[v];
                            if (!currentVehicle) continue;

                            if (IsVehicleBroken(currentVehicle)) continue;

                            Vector3 vehicleWorldPos = GetVehicleWorldPosition(currentVehicle);

#if IS_DEV
                            // LOGI("ARCA", "Vehicle %d: World pos (%.2f, %.2f, %.2f)", v, vehicleWorldPos.x, vehicleWorldPos.y, vehicleWorldPos.z);
#endif

                            if (vehicleWorldPos.x == 0.0f && vehicleWorldPos.y == 0.0f && vehicleWorldPos.z == 0.0f) continue;

                            Vector3 vehicleScreenPos = Camera$$WorldToScreenPoint(currentCamera, vehicleWorldPos);

#if IS_DEV
                            // LOGI("ARCA", "Vehicle %d: Screen pos (%.2f, %.2f, %.2f)", v, vehicleScreenPos.x, vehicleScreenPos.y, vehicleScreenPos.z);
#endif

                            if (vehicleScreenPos.z <= 0) continue;
                            if (vehicleScreenPos.x < -100 || vehicleScreenPos.x > glWidth + 100) continue;
                            if (vehicleScreenPos.y < -100 || vehicleScreenPos.y > glHeight + 100) continue;

                            float distance = GetVehicleDistance(currentVehicle, cameraPos);
                            if (distance > VEHICLE_MAX_DISTANCE || distance < 1.0f) continue;

                            DrawVehicleLine(draw, vehicleScreenPos, (float)glWidth, (float)glHeight);
                            DrawVehicleBox(draw, vehicleScreenPos, (float)glWidth, (float)glHeight);
                            DrawVehicleDistance(draw, vehicleScreenPos, distance, (float)glHeight);

                            if (Config.View.Vehicle.Health) {
                                float health = GetVehicleHealth(currentVehicle);
                                float maxHealth = GetVehicleMaxHealth(currentVehicle);
                                float healthPercentage = GetVehicleHealthPercentage(currentVehicle);

#if IS_DEV
                                // LOGI("ARCA", "Vehicle %d: Health %.2f/%.2f (%.1f%%)", v, health, maxHealth, healthPercentage * 100.0f);
#endif

                                DrawVehicleHealth(draw, vehicleScreenPos, healthPercentage, (float)glHeight);
                            }

                            DrawVehicleLabel(draw, vehicleScreenPos, (float)glHeight);
                        }
                    }
                }
            }
        }

        signal(SIGSEGV, original_SIGSEGV);
        signal(SIGABRT, original_SIGABRT);

        return nullptr;
}