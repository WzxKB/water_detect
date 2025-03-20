#include "gui_guider.h"
#include <lvgl.h>
#include <string>
class Application
{
public:
    static Application &GetInstance()
    {
        static Application instance;
        return instance;
    }
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void Start(lv_ui *uis);

private:
    Application();
    ~Application();
    void MainLoop();
    void AdcDetectLoop();
    void get_config_value_label(std::string &label, char la);
};