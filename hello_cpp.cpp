#include <iostream>

class IDoor {
 public:
  virtual void GetDescription() = 0;
};

class WoodenDoor : public IDoor{
 public:
  void GetDescription() override {
    std::cout << "I am a wooden door" << std::endl;
  }
};

class IronDoor : public IDoor {
 public:
  void GetDescription() override {
    std::cout << "I am a iron door" << std::endl;
  }
};

class IDoorFittingExpert {
 public:
  virtual void GetDescription() = 0;
};

class Carpenter : public IDoorFittingExpert {
  void GetDescription() override {
    
  }
}

class Solution {
public:
    //构造两个哈希表，origin是 目标字符串target 的各字符数量, count为 滑动字符串 字符数量的计数器
    unordered_map <char, int> origin, count;

    bool check() {
        // 检测函数，检测经过 滑动窗口 的字符串是否全包含 target 的字符
        for (const auto &p: origin) {
            if (count[p.first] < p.second) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string str, string target) {
        //确定target字符串各字符数量，存到 哈希表 origin
        for (const auto &c: target) {
            ++origin[c];
        }
        // 定义左指l和右指r，为了能使字符串无论多长，在（r - l + 1 < len）第一次判断都能继续下去，
        // 将滑动确定的字符串长len初始指设为INT_MAX,ansL为最终字符串的左指。
        int left = 0, right = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        // 滑动窗口的右边界 到达 源字符串的末尾，循环结束
        while (right < int(str.size())) {
            //右指右移，如果字母是target中字母，计数器count中的该字母数量加1
            if (origin.find(str[++right]) != origin.end()) {
                ++count[str[right]];
            }
            // 若滑动窗口的元素 已全部包含 目标字符串的元素，并且 左右索引依然有序，则开始 收缩窗口
            while (check() && left <= right) {
                // 右移发现该字母不在t中，检测现在滑动确定的字符串是否全包含t，如果是在判断现在字符串是否为历次最短，如果是，长度赋予len，左指赋予ansL
                if (right - left + 1 < len) {
                    // 更新滑动窗口长度，并一步步缩小左边界
                    len = right - left + 1;
                    ansL = left;
                }
                // 若左边界字符是target中的字符，则计数器count中的该字母数量，左边界向右缩进
                if (origin.find(str[left]) != origin.end()) {
                    --count[str[left]];
                }
                ++left;//左指右移，如果是t中字符，减去cnt中该字符数量1
            }//此循坏直到滑动确定的字符串不满足check为止，再次开始右指右移
        }//遍历完成

        return ansL == -1 ? string() : str.substr(ansL, len);//判断最终字符串是否为空，然后输出结果
    }
};
