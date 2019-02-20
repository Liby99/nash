#include <nash/nash.h>

using namespace nash;

class SHSphereViewer : public Viewer {
public:
  constexpr static int SIDEBAR_WIDTH = 300;
  constexpr static int MAX_L = 16;

  SHSphereViewer(int width, int height, Scene & scene)
      : l(0), m(0), sphere(0, 0), Viewer(width, height, "Spherical Harmonics Sphere", scene) {
    scene.addObject(sphere);

    // Start setting up the viewer
    using namespace nanogui;

    // First tweak the existing window and canvas.
    sceneWindow->setPosition({ SIDEBAR_WIDTH, 0 });
    sceneWindow->setTitle("Sphere Viewer");
    sceneCanvas->setSize(width - 2 * PADDING - SIDEBAR_WIDTH, height - HEADER_HEIGHT - 2 * PADDING);

    // Then add a sidebar containing two sliders
    sidebarWindow = new Window(this, "Parameters");
    sidebarWindow->setSize({ SIDEBAR_WIDTH, height - 2 * PADDING });
    sidebarWindow->setLayout(new GroupLayout(0));
    sidebarScrollPanel = new VScrollPanel(sidebarWindow);
    sidebarScrollPanel->setFixedSize({ SIDEBAR_WIDTH, height - HEADER_HEIGHT });
    sliderHolder = new Widget(sidebarScrollPanel);
    sliderHolder->setLayout(new GroupLayout());
    lLabel = new Label(sliderHolder, getLLabel());
    lSlider = new Slider(sliderHolder);
    lSlider->setRange({ 0, MAX_L });
    lSlider->setValue(0);
    mLabel = new Label(sliderHolder, getMLabel());
    mSlider = new Slider(sliderHolder);
    mSlider->setRange({ -l, l });
    mSlider->setValue(0);

    // Set slider callbacks
    lSlider->setCallback([this](float fl) { this->setL(fl); });
    mSlider->setCallback([this](float fm) { this->setM(fm); });
  }

  void setL(float fl) {
    int tl = std::round(fl);
    lSlider->setValue(tl);
    if (tl != l) {
      l = tl;
      lLabel->setCaption(getLLabel());
      mSlider->setRange({ -l, l });
      if (std::abs(m) > l) {
        m = m > 0 ? l : -l;
        mSlider->setValue(m);
        mLabel->setCaption(getMLabel());
      }
      sphere = SHSphere(l, m);
    }
  }

  void setM(float fm) {
    int tm = std::round(fm);
    mSlider->setValue(tm);
    if (tm != m) {
      m = tm;
      sphere = SHSphere(l, m);
      mLabel->setCaption(getMLabel());
    }
  }

  std::string getLLabel() {
    return "L: (" + std::to_string(l) + ")";
  }

  std::string getMLabel() {
    return "M: (" + std::to_string(m) + ")";
  }
private:
  nanogui::Window *sidebarWindow;
  nanogui::VScrollPanel *sidebarScrollPanel;
  nanogui::Widget *sliderHolder;
  nanogui::Label *lLabel, *mLabel;
  nanogui::Slider *lSlider, *mSlider;
  int l, m;
  SHSphere sphere;
};

int main(int argc, char * argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  SHSphereViewer viewer(1280, 720, scene);
  viewer.start();

  Nash::shutdown();
}