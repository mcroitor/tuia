/**
 * @brief Create a simple UI using TUIA.
 * UI contains a dialog box with a title, a message, and a button.
 * Dialog box is centered on the screen.
 * - Dialog box size: 40x10
 * - Dialog color background: Blue
 * - Dialog color border: White
 * - Dialog color text: White
 * 
 * - Title: "Dialog Box"
 * - Message: "This is a dialog box."
 * - Button: "OK"
 */
#include "tuia.hpp"

using usm::graphics::TUIA;
using usm::graphics::Color;
using usm::graphics::Image;

int main(){
    TUIA::Init();
    TUIA::SetBackgroundColor(usm::graphics::terminal::BackgroundColor::Black);
    TUIA::ClearScreen();

    // Dialog box details
    const int dialogWidth = 40;
    const int dialogHeight = 10;
    const int dialogX = (TUIA::GetScreenSize().GetX() - dialogWidth) / 2;
    const int dialogY = (TUIA::GetScreenSize().GetY() - dialogHeight) / 2;
    const Color dialogColorBackground = Color(0, 0, 170);
    const Color dialogColorBorder = Color(255, 255, 255);
    const Color dialogColorText = Color(255, 255, 255);

    // Title
    const std::string title = "Dialog Box";
    const int titleX = dialogX + (dialogWidth - title.size()) / 2;
    const int titleY = dialogY + 1;

    // Message
    const std::string message = "This is a dialog box.";
    const int messageX = dialogX + (dialogWidth - message.size()) / 2;
    const int messageY = dialogY + 3;

    // Button
    const std::string button = "OK";
    const int buttonX = dialogX + (dialogWidth - button.size()) / 2;
    const int buttonY = dialogY + dialogHeight - 3;

    // Draw dialog box
    TUIA::DrawBlock({dialogX, dialogY}, dialogWidth, dialogHeight, dialogColorBackground);

    // Draw title
    TUIA::WriteLine({titleX, titleY}, title);

    // Draw message
    TUIA::WriteLine({messageX, messageY}, message);

    // Draw button
    TUIA::WriteLine({buttonX, buttonY}, button);

    return 0;
}