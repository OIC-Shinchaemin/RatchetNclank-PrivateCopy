#ifndef MY_UTILITY_H
#define MY_UTILITY_H


#include "My/Core/Trait.h"


#ifdef max
#undef max
#endif // max
#ifdef min
#undef min
#endif // min


namespace ut {
static std::uint32_t GetDigit(std::uint32_t num) {
    if (num == 0) {
        return 1;
    } // if
    return static_cast<std::uint32_t> (std::log10(num) + 1);
}
static int Approximate(const std::vector<int>& vec, int value) {
    return *std::min_element(vec.begin(), vec.end(), [&value](int a, int b) {
        return
            std::abs(std::max(value, a) - std::min(value, a)) <
            std::abs(std::max(value, b) - std::min(value, b));
    });
}
template <class T>
void SafeDelete(T*& ptr) {
    if (ptr != nullptr) {
        delete ptr;
        ptr = nullptr;
    } // if
}
template<class T, std::size_t Size>
std::size_t ArraySize(const T(&)[Size]) {
    return Size;
}
template <class... Args>
auto CountArguments(Args... args) {
    return sizeof...(args);
}
template<class... Args>
auto Sum(Args... args) {
    return (args + ...);
}
template<class... Args>
auto Average(Args... args) {
    return (args + ...) / CountArguments(args...);
}

static void IOSetting(void) {
    std::cout << std::fixed << std::setprecision(7) << std::boolalpha;
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

template<class To, class From>
To lexical_cast(From from) {
    To result;
    std::stringstream ss;
    ss << from;
    ss >> result;
    return result;
}

template<typename T>
void InsertAscend(std::vector<T>& out, const T& elem) {
    auto it = out.begin();
    auto it_end = out.end();
    for (; it != it_end; ++it) {
        if (elem < (*it)) {
            break;
        } // if
    } // for
    out.insert(it, elem);
}

template <class T>
bool SwapPopback(std::vector<T>& out, const T& elem) {
    auto it = std::find(out.begin(), out.end(), elem);
    if (it == out.end()) {
        return false;
    } // if
    std::iter_swap(it, out.end() - 1);
    out.pop_back();
    return true;
}

template <class T>
bool EraseFind(std::vector<T>& out, const T& elem) {
    auto it = std::find(out.begin(), out.end(), elem);
    if (it == out.end()) {
        return false;
    } // if
    out.erase(it);
    return true;
}

template<class T>
void EraseRemove(std::vector<T>& out, const T& elem) {
    out.erase(std::remove(out.begin(), out.end(), elem), out.end());
}

template<class T, class Condition>
void EraseRemove(std::vector<T>& out, Condition condition) {
    out.erase(std::remove_if(out.begin(), out.end(), condition), out.end());
}

template <class T, class...Args>
std::shared_ptr<T> MakeSharedWithRelease(Args...args) {
    return std::shared_ptr<T>(new T(args...), [](T* ptr) {
        ptr->Release();
        ut::SafeDelete(ptr);
    });
}

static int GenerateRandom(const int min, const int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return random(engine);
}

static float GenerateRandomF(const float min, const float max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_real_distribution<> random(min, max);
    return static_cast<float>(random(engine));
}

static bool ParseJsonDocument(const char* path, rapidjson::Document& document) {
    std::ifstream file(path);
    // ファイルを開けないならfalseを返す
    if (!file.is_open()) {
        return false;
    } // if
    // 読み込み
    std::stringstream stream;
    stream << file.rdbuf();
    std::string temp = stream.str();
    rapidjson::StringStream str(temp.c_str());
    document.ParseStream(str);
    return true;
}
}
#endif // !MY_UTILITY_H