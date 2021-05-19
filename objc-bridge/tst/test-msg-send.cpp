#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/class_builder.hpp"

#include <limits>

#undef Nil
#include "m4c0/test.hpp"

struct point {
  double x;
  double y;
};
static point operator+(point a, point b) {
  return { a.x + b.x, a.y + b.y };
}
static bool operator==(point a, point b) {
  return (std::abs(a.x - b.x) < std::numeric_limits<decltype(point::x)>::epsilon())
      && (std::abs(a.y - b.y) < std::numeric_limits<decltype(point::y)>::epsilon());
}
static std::ostream & operator<<(std::ostream & o, const point & p) {
  return o << "point[" << p.x << "," << p.y << "]";
}

// Larger than 2 double registers
struct rect {
  point x;
  point y;
};
static rect operator+(rect a, rect b) {
  return { a.x + b.x, a.y + b.y };
}
static bool operator==(rect a, rect b) {
  return (a.x == b.x) && (a.y == b.y);
}
static std::ostream & operator<<(std::ostream & o, const rect & p) {
  return o << "rect[" << p.x << ";" << p.y << "]";
}

template<class Tp>
static Tp sum(void * /*obj*/, void * /*sel*/, Tp a, Tp b) {
  return a + b;
}

template<class Tp>
static void run_test(Tp a, Tp b, const char * sign) {
  static constexpr const char * method = "sum:with:";
  m4c0::objc::autorelease_pool pool;

  auto imp = m4c0::objc::to_imp(sum<Tp>);
  const char * cls = m4c0::objc::class_builder("NSObject").add_method(method, imp, sign).build();
  auto * obj = m4c0::objc::objc_msg_send<void *>(objc_getClass(cls), "new");

  Tp res = m4c0::objc::objc_msg_send<Tp>(obj, method, a, b);
  AssertThat(res, Is().EqualTo(a + b));
}

go_bandit([] { // NOLINT
  describe("objc_msg_send", [] {
    it("can invoke basic methods", [] {
      static constexpr const int a = 28347;
      static constexpr const int b = 34573;
      run_test(a, b, "i@:ii");
    });
    it("can invoke fpret methods", [] {
      static constexpr const double a = 28.347;
      static constexpr const double b = 34.573;
      run_test(a, b, "d@:dd");
    });
    it("can invoke fake stret methods", [] {
      static constexpr const double a = 28.347;
      static constexpr const double b = 34.573;
      point pa { a, 0 };
      point pb { 0, b };
      run_test(pa, pb, "{point=dd}@:{point=dd}{point=dd}");
    });
    it("can invoke real stret methods", [] {
      static constexpr const double x = 28.347;
      static constexpr const double y = 34.347;
      static constexpr const double z = 28.573;
      static constexpr const double w = 34.573;
      rect ra { { x, 0 }, { y, 0 } };
      rect rb { { 0, z }, { 0, w } };
      run_test(ra, rb, "{rect=dddd}@:{rect=dddd}{rect=dddd}");
    });
  });
});
