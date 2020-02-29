#include <stdint.h>
#include <string>
#include <vector>
#include <ostream>

static inline volatile uint64_t cpu_cycles(void) {
#if defined(__amd64__) || defined(__x86_64__) 
    unsigned a, d; 
    asm volatile("rdtsc" : "=a" (a), "=d" (d)); 
    return ((uint64_t)a) | (((uint64_t)d) << 32); 
#elif defined(__aarch64__)
    int64_t virtual_timer_value;
    asm volatile("mrs %0, cntvct_el0" : "=r"(virtual_timer_value));
    return virtual_timer_value;
#endif
    return 0;
} 


class profiler {
    public:
    profiler(const std::string &name, unsigned int reserve=10) {
        _samples.reserve(reserve);
    }
    ~profiler(void) {
    }

    void iteration(unsigned int i) {
        // TODO
    }
    void start(const char *name) {
        _samples.emplace_back(sample(name));
        uint64_t &start_clock = _samples.back().start;
        start_clock = cpu_cycles();
    }
    void end(void) {
        uint64_t end_clock = cpu_cycles();
        _samples.back().end = end_clock;
    }

    void report(std::ostream &out) {
        out << "Times for " << _name << "\n";
        double prev_diff = 0;
        for (auto &i : _samples) {
            uint64_t diff = i.end - i.start;
            if (prev_diff == 0) {
                out << "  "   << i.name  << " : " << diff << "\n";
            } else {
                double ratio = ((double) diff) / prev_diff;
                out << "  "   << i.name  << " : " << diff << " : " << (1/ratio) << "x\n";                
            }
            prev_diff = (double) diff;
        }
    }
private :
    struct sample {
        sample(const char *name) 
            : start(0)
            , end(0)
            , name(name)
            {
            }
        uint64_t start;
        uint64_t end;
        const char *name;
    };
    const std::string _name;
    std::vector<sample> _samples;
};
