#ifndef TRIANGLE_H
#define TRIANGLE_H

namespace nash {
  class Triangle {
  public:
    Triangle(const Vector3f a, const Vector3f b, const Vector3f c);

    Triangle(const std::initializer_list<Vector3f> vertices);

    bool intersect(const Ray &ray, Intersection &intersection);

  private:
    void calculateNormal();

    std::vector<Vector3f> vertices_;
    Vector3f normal_;
  };
}

#endif