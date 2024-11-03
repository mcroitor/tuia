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

using usm::graphics::Point;
using usm::graphics::Color;
using usm::graphics::BackgroundColor;
using usm::graphics::ForegroundColor;
using usm::graphics::terminal::FromBackgroundColor;
using usm::graphics::Image;
using usm::graphics::TUIA;

class DialogBox
{
    Point position;
    std::string title;
    std::string message;
    std::string button;
    int width;
    int height;

    void DrawBox(){
        TUIA::SetBackgroundColor(BackgroundColor::White);
        TUIA::ClearBlock(position, width, height);
    }
    void DrawTitle(){
        TUIA::SetBackgroundColor(BackgroundColor::Blue);
        TUIA::SetForegroundColor(ForegroundColor::BrightWhite);
        Point titlePosition {position.GetX() + 1, position.GetY() + 1};
        TUIA::ClearBlock(titlePosition, width - 2, 1);
        TUIA::WriteLine(titlePosition, title);
    }
    void DrawMessage(){
        Point messagePosition {
            position.GetX() + (int)message.size() / 2 + 1, 
            position.GetY() + height / 2};
        TUIA::SetBackgroundColor(BackgroundColor::White);
        TUIA::SetForegroundColor(ForegroundColor::Black);
        TUIA::WriteLine(messagePosition, message);
    }
    void DrawButton(){

        Point buttonPosition {
            position.GetX() + width / 2 - (int)button.size() / 2, 
            position.GetY() + height - 2};
        TUIA::SetBackgroundColor(BackgroundColor::BrightWhite);
        TUIA::SetForegroundColor(ForegroundColor::Black);
        TUIA::WriteLine(buttonPosition, button);
    }
public:
    DialogBox(int width, int height, const std::string &title) 
        : width(width), height(height), title(title), message {}, button {"OK"} {}
    void SetMessage(const std::string &message) { this->message = message; }
    void SetButtonText(const std::string &button) { this->button = button; }
    void SetTitle(const std::string &title) { this->title = title; }

    void Show() {
        DrawBox();
        DrawTitle();
        DrawMessage();
        DrawButton();
    }
};

int main()
{
    TUIA::Init();
    TUIA::SetBackgroundColor(usm::graphics::terminal::BackgroundColor::Black);
    TUIA::ClearScreen();

    // Dialog box details
    const int dialogWidth = 40;
    const int dialogHeight = 10;

    DialogBox dialog(dialogWidth, dialogHeight, "Dialog Box");
    dialog.SetMessage("This is a dialog box.");
    dialog.SetButtonText("OK");

    dialog.Show();
    return 0;
}