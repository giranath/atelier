#include "string_name.hpp"
#include "hash.hpp"
#include <cstdint>
#include <unordered_map>
#include <utility>

namespace at
{

struct string_table_entry
{
    std::string content = {};
    uint64_t hash = 0;
    uint32_t refcount = 0;

    string_table_entry() = default;
};

class string_table
{
    std::unordered_map<uint64_t, string_table_entry> entries_;

    string_table() = default;

public:
    string_table_entry* addref(std::string_view str)
    {
        if(str.empty())
        {
            return nullptr;
        }

        const uint64_t str_hash = hash(str);

        string_table_entry* entry = nullptr;

        auto it = entries_.find(str_hash);
        if(it != entries_.end())
        {
            entry = &it->second;
        }
        else
        {
            string_table_entry& new_entry = entries_[str_hash];
            new_entry.content = str;
            new_entry.hash = str_hash;

            entry = &new_entry;
        }

        ++entry->refcount;

        return entry;
    }

    void release(string_table_entry* entry)
    {
        if(entry)
        {
            --entry->refcount;

            if(entry->refcount == 0)
            {
                entries_.erase(entry->hash);
            }
        }
    }

    static string_table& get()
    {
        static string_table singleton;

        return singleton;
    }
};

string_name::string_name()
: entry_{nullptr}
{

}

string_name::string_name(std::string_view str)
: entry_(string_table::get().addref(str))
{

}

string_name::string_name(const string_name& other) noexcept
: entry_{other.entry_}
{
    if(entry_)
    {
        ++entry_->refcount;
    }
}

string_name::string_name(string_name&& other) noexcept
: entry_{std::exchange(other.entry_, nullptr)}
{

}

string_name::~string_name()
{
    if(entry_)
    {
        string_table::get().release(entry_);
    }
}

string_name& string_name::operator=(const string_name& other) noexcept
{
    if(this != &other)
    {
        string_table::get().release(entry_);

        entry_ = other.entry_;

        ++entry_->refcount;
    }

    return *this;
}

string_name& string_name::operator=(string_name&& other) noexcept
{
    if(this != &other)
    {
        string_table::get().release(entry_);

        entry_ = std::exchange(other.entry_, nullptr);
    }

    return *this;
}

bool string_name::operator==(const string_name& other) const noexcept
{
    return entry_ == other.entry_;
}

bool string_name::operator!=(const string_name& other) const noexcept
{
    return entry_ != other.entry_;
}

void string_name::clear() noexcept
{
    string_table::get().release(entry_);
    entry_ = nullptr;
}

const char* string_name::c_str() const noexcept
{
    return entry_ ? entry_->content.c_str() : nullptr;
}

std::string string_name::string() const noexcept
{
    return entry_ ? entry_->content : std::string{};
}

bool string_name::empty() const noexcept
{
    return entry_ == nullptr;
}

string_name operator""_sname(const char* str, std::size_t len)
{
    return string_name{std::string_view{str, len}};
}

}