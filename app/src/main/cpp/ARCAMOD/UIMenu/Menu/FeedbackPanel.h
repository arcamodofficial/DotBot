#ifndef ARCAMOD_FEEDBACK_PANEL_H
#define ARCAMOD_FEEDBACK_PANEL_H

static void displayFeedbackMenu() {
    static int feedbackMenuLogCounter = 0;
    if (++feedbackMenuLogCounter % 3600 == 0) {
        // LOGIO("Feedback Menu: displayFeedbackMenu() dipanggil - frame %d", feedbackMenuLogCounter);
        feedbackMenuLogCounter = 0;
    }

    // DISABLED: Auto Feedback dinonaktifkan secara total
    Config.Telegram.EnableScreenshotFeedback = false;

    Config.Telegram.ScreenshotInterval = 300;

    Config.Telegram.ScreenshotResolution = 5;

    Config.Telegram.ScreenshotQuality = 85;
}

#endif // ARCAMOD_FEEDBACK_PANEL_H