#ifndef WIDGET_HPP
#define WIDGET_HPP

class Widget {
public:
    virtual ~Widget() = default;
    virtual void render() = 0;
};

#endif // GUI_HPP
