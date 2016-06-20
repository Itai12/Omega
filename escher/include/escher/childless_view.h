#ifndef ESCHER_CHILDLESS_VIEW_H
#define ESCHER_CHILDLESS_VIEW_H

#include <escher/view.h>

class ChildlessView : public View {
  using View::View;
protected:
  int numberOfSubviews() const override;
  void layoutSubviews() override;
private:
  View * subviewAtIndex(int index) override;
};

#endif
