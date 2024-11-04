#include <bits/stdc++.h>

using namespace std;

struct Editor
{

private:
    struct Block
    {
        array<int, 26> counter;
        string str;

        Block() = default;
        Block(const string &_str) : counter(), str(_str)
        {
            for (auto c : str)
                counter[c - 'a'] += 1;
        }
    };

    struct Node
    {
        shared_ptr<Block> block;
        shared_ptr<Node> next;

        Node() = default;
        Node(const shared_ptr<Block> &_data, const shared_ptr<Node> &_next) : block(_data), next(_next) {}
        Node(const Node &o) : block(o.block), next(o.next) {}
    };

    map<int, shared_ptr<Node>> texts;
    map<int, int> texts_size;
    int version_counter;
    int current_version;

    static constexpr int max_versions = 20000;
    static constexpr int min_block_size = 64;
    static constexpr int block_size = 128;
    static constexpr int max_block_size = 256;

public:
    Editor() : texts(), texts_size(), version_counter(0), current_version(0)
    {
        texts[0] = make_shared<Node>(
            make_shared<Block>(),
            make_shared<Node>(
                make_shared<Block>(),
                nullptr));
        texts_size[0] = 0;
    }

private:
    pair<shared_ptr<Node>, shared_ptr<Node>> _make_text(const string &str)
    {
        shared_ptr<Node> start = make_shared<Node>(make_shared<Block>(), nullptr);
        auto ptr = start;
        int c_pos = 0;
        while (c_pos < str.size())
        {
            string substr = str.substr(c_pos, block_size);
            c_pos += block_size;
            ptr->next = make_shared<Node>(make_shared<Block>(substr), nullptr);
            ptr = ptr->next;
        }
        return {start->next, ptr};
    }

    pair<shared_ptr<Node>, shared_ptr<Node>> _get_text(int new_version, int pos, int len)
    {
        auto ptr = texts[new_version]->next;
        shared_ptr<Node> text_begin = nullptr;
        shared_ptr<Node> text_end = nullptr;

        int c_pos = 0;
        while (c_pos < pos)
        {
            c_pos += ptr->block->str.size();
            ptr = ptr->next;
        }
        text_begin = ptr;
        while (c_pos + ptr->block->str.size() < pos + len)
        {
            c_pos += ptr->block->str.size();
            ptr = ptr->next;
        }
        text_end = ptr;
        auto n_text_begin = make_shared<Node>(*text_begin);
        auto n_ptr = n_text_begin;
        while (n_ptr->next != text_end->next)
        {
            n_ptr->next = make_shared<Node>(*n_ptr->next);
            n_ptr = n_ptr->next;
        }
        n_ptr->next = nullptr;
        return {n_text_begin, n_ptr};
    }

    void _copy(int new_version)
    {
        auto ptr = texts[current_version];
        auto n_ptr = make_shared<Node>(*ptr);
        for (auto a = ptr, b = n_ptr; a->next != nullptr; a = a->next, b = b->next)
        {
            b->next = make_shared<Node>(*a->next);
        }
        texts[new_version] = n_ptr;
        texts_size[new_version] = texts_size[current_version];
    }

    void _split(int new_version, int pos)
    {
        auto ptr = texts[new_version]->next;
        int c_pos = 0;
        while (ptr->block->str.size() > 0 && c_pos + ptr->block->str.size() <= pos)
        {
            c_pos += ptr->block->str.size();
            if (ptr->next == nullptr)
                ptr->next = make_shared<Node>(make_shared<Block>(), nullptr);
            ptr = ptr->next;
        }
        if (c_pos != pos)
        {
            auto block = ptr->block;
            auto next = ptr->next;
            auto n_block1 = make_shared<Block>(block->str.substr(0, pos - c_pos));
            auto n_block2 = make_shared<Block>(block->str.substr(pos - c_pos));
            ptr->block = n_block1;
            ptr->next = make_shared<Node>(n_block2, next);
        }
    }

    void _insert(int new_version, int pos, shared_ptr<Node> text_begin, shared_ptr<Node> text_end)
    {
        auto prev_ptr = texts[new_version];
        auto ptr = prev_ptr->next;
        int c_pos = 0;
        while (c_pos < pos)
        {
            c_pos += ptr->block->str.size();
            prev_ptr = ptr;
            ptr = ptr->next;
        }
        assert(c_pos == pos);
        auto next = ptr->next;
        prev_ptr->next = text_begin;
        text_end->next = ptr;
    }

    void _erase(int new_version, int pos, int len)
    {
        auto prev_ptr = texts[new_version];
        auto ptr = prev_ptr->next;
        int c_pos = 0;
        while (c_pos < pos)
        {
            c_pos += ptr->block->str.size();
            prev_ptr = ptr;
            ptr = ptr->next;
        }
        assert(c_pos == pos);
        while (c_pos < pos + len)
        {
            c_pos += ptr->block->str.size();
            ptr = ptr->next;
        }
        prev_ptr->next = ptr;
    }

    int _query(int new_version, int pos, int len, int ch)
    {
        auto ptr = texts[new_version]->next;
        int res = 0;
        int c_pos = 0;
        while (c_pos < pos)
        {
            c_pos += ptr->block->str.size();
            ptr = ptr->next;
        }
        assert(c_pos == pos);
        while (c_pos < pos + len)
        {
            res += ptr->block->counter[ch];
            c_pos += ptr->block->str.size();
            ptr = ptr->next;
        }
        return res;
    }

    void _maintain(int new_version)
    {
        auto prev_ptr = texts[new_version];
        auto ptr = prev_ptr->next;
        while (ptr->next || ptr->block->str.size() > max_block_size)
        {
            if (ptr->block->str.size() < min_block_size)
            {
                auto n_ptr = make_shared<Node>(
                    make_shared<Block>(ptr->block->str + ptr->next->block->str),
                    ptr->next->next);
                prev_ptr->next = n_ptr;
                ptr = n_ptr;
            }
            else if (ptr->block->str.size() > max_block_size)
            {
                auto block = ptr->block;
                ptr->block = make_shared<Block>(block->str.substr(0, block_size));
                auto n_ptr = make_shared<Node>(
                    make_shared<Block>(block->str.substr(block_size)),
                    ptr->next);
                ptr->next = n_ptr;

                prev_ptr = ptr;
                ptr = ptr->next;
            }
            else
            {
                prev_ptr = ptr;
                ptr = ptr->next;
            }
        }
    }

    void _update_version(int new_version)
    {
        int v = (new_version - max_versions);
        if (texts.count(v))
        {
            texts.erase(v);
            texts_size.erase(v);
        }
        current_version = new_version;
    }

    void _print(int new_version)
    {
        for (auto ptr = texts[new_version]->next; ptr != nullptr; ptr = ptr->next)
        {
            std::cout << "{" << ptr->block->str << "} ";
        }
        cout << endl;
    }

    // ---------------------------------------------------------

public:
    void insert(int pos, const string &str);
    void erase(int pos, int len);
    void copy(int pos1, int len, int pos2);
    int query(int pos, int len, int ch);
    void jump(int version);
    void print();
};
// ____qcodep____

// 如果你看到这个代码，我倍感抱歉，但我真的是因为第一次写的时候没看到要填空
// 这个题无聊死了

#include <stdio.h>
#include <vector>
#include <string>
#include <cctype>

std::string insert(const std::string &s1, int p, const std::string &s2)
{
    return s1.substr(0, p) + s2 + s1.substr(p);
}

std::string remove(const std::string &s1, int p, int l)
{
    return s1.substr(0, p) + s1.substr(p + l);
}

std::string duplicate(const std::string &s1, int p1, int l, int p2)
{
    return s1.substr(0, p2) + s1.substr(p1, l) + s1.substr(p2);
}

int query(const std::string &s1, int p1, int l, char c)
{
    const char *cstr = s1.c_str();
    const size_t size = s1.length();
    int cnt = 0;
    for (int i = 0; i < l; i++)
        if (cstr[p1 + i] == c)
            ++cnt;
    return cnt;
}

char buffer[12000];

int main()
{
    int n;
    scanf("%d\n", &n);
    std::vector<std::string> vec;
    vec.reserve(n + 1);
    vec.push_back("");
    std::string that = "";
    for (int i = 0; i < n; i++)
    {
        int op;
        do
        {
            op = getchar();
        } while (isspace(op));
        int p1, l, p2, ret;
        char c;
        std::string buffer2;
        switch (op)
        {
        case 'i':
            scanf("%d %s", &p1, buffer);
            buffer2 = buffer;
            that = insert(that, p1, buffer2);
            vec.push_back(that);
            break;

        case 'e':
            scanf("%d %d", &p1, &l);
            that = remove(that, p1, l);
            vec.push_back(that);
            break;

        case 'c':
            scanf("%d %d %d", &p1, &l, &p2);
            that = duplicate(that, p1, l, p2);
            vec.push_back(that);
            break;

        case 'q':
            scanf("%d %d %c", &p1, &l, &c);
            ret = query(that, p1, l, c);
            printf("%d\n", ret);
            break;

        case 'j':
            scanf("%d", &l);
            that = vec[l];
            break;
        }
    }
    printf("%s\n", that.c_str());
    return 0;
}

// 上天啊，请原谅我使用一点魔法和禁术吧！
// 我真的不是懒；但这个题真的太无聊了，我不想再写一遍这玩意。
// 请饶恕我的亵渎！
#define main static __main__

// ____qcodep____

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    auto editor = Editor();
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "i")
        {
            int pos;
            string str;
            cin >> pos >> str;
            editor.insert(pos, str);
        }
        else if (cmd == "e")
        {
            int pos, len;
            cin >> pos >> len;
            editor.erase(pos, len);
        }
        else if (cmd == "c")
        {
            int pos1, len, pos2;
            cin >> pos1 >> len >> pos2;
            editor.copy(pos1, len, pos2);
        }
        else if (cmd == "j")
        {
            int v;
            cin >> v;
            editor.jump(v);
        }
        else if (cmd == "q")
        {
            int pos, len;
            string ch;
            cin >> pos >> len >> ch;
            cout << editor.query(pos, len, ch[0] - 'a') << endl;
        }
    }
    editor.print();
    return 0;
}
