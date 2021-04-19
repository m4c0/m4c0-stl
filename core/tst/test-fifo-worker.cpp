#include "m4c0/fifo_worker.hpp"
#include "m4c0/test.hpp"

go_bandit([] { // NOLINT
  describe("fifo_worker", [] {
    m4c0::fifo_worker<std::vector<int> &> q {};

    q.enqueue([](auto & a) {
      a.push_back(1);
    });
    q.enqueue([](auto & a) {
      a.push_back(2);
    });

    it("enqueues and process in order", [&] {
      std::vector<int> res {};
      q.process(res);

      std::vector<int> expected {};
      expected.push_back(1);
      expected.push_back(2);
      AssertThat(res, EqualsContainer(expected));
    });
    it("process only once", [&] {
      std::vector<int> res {};
      q.process(res);

      AssertThat(res, Is().Empty());
    });
  });
});
