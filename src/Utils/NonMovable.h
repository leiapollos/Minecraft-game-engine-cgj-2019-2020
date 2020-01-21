#ifndef NON_MOVABLE_H
#define NON_MOVABLE_H

class NonMovable {
  public:
    NonMovable(NonMovable &&) = delete;

    NonMovable &operator=(NonMovable &&) = delete;

  protected:
    NonMovable() = default;
};

#endif