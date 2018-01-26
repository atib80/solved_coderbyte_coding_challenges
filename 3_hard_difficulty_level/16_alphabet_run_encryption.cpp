/*
Coderbyte coding challenge: Alphabet Run Encryption

Using the C++ language, have the function AlphabetRunEncryption(str) read the str parameter being passed
which will be an encrypted string and your program should output the original decrypted string.
The encryption being used is the following:
For every character i in str up to the second to last character, take the i and i+1 characters
and encode them by writing the letters of the alphabet, in order, that range in the same direction between those chosen characters.
For example: if the original string were bo then it would be encoded as cdefghijklmn,
but if the string were boa then bo is encoded as cdefghijklmn and oa is encoded as nmlkjihgfedcb
with the final encrypted string being cdefghijklmnnmlkjihgfedcb.
So str may be something like the encrypted string just written,
and your program should decrypt it and output the original message.

The input string will only contains lowercase characters (a...z).
There are also three important rules to this encryption based on specific character sequences.

1) If the original string contains only one letter between two chosen characters,
as the string ac then this would be encrypted as bR with R standing for what direction
in the alphabet to go in determining the original characters.
The encrypted string bR represents ac but the encrypted string bL represents ca (R = right, L = left).

2) If the original string contains zero letters between two chosen characters,
such as the string ab then this would be encrypted as abS, with S representing the fact
that no decryption is needed on the two letters preceding S.
For example, if the original string were aba then the encryption would be abSbaS,
but be careful because decrypting this you get abba, but the actual original string is aba.

3) If the original string contains a repeat of letters, such as the string acc then this would be encrypted as bRcN,
with N representing the fact that no change in characters occurred on the character preceding N.
The input string will never only be composed of repeated characters.

Sample test cases:

Input:  "bcdefghijklmnopqrstN"
Output: "att"

Input:  "abSbaSaNbR"
Output: "abaac"
*/

#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string &str)
{
    const size_t str_len{str.length()};

    if (!str_len)
        return string{};

    size_t first{}, last{str_len - 1};

    for (; first <= last; ++first)
    {
        if (!isspace(str[first]))
            break;
    }

    if (first > last)
        return string{};

    for (; last > first; --last)
    {
        if (!isspace(str[last]))
            break;
    }

    return str.substr(first, last - first + 1);
}

vector<string> split(const string &source, const char *needle,
                     size_t const max_count = string::npos)
{
    vector<string> parts{};

    string needle_st{needle};

    const size_t source_len{source.length()};

    const size_t needle_len{needle_st.size()};

    if ((0u == source_len) || (0u == needle_len))
        return parts;

    size_t number_of_parts{}, prev{};

    while (true)
    {
        const size_t current{source.find(needle_st, prev)};

        if (string::npos == current)
            break;

        number_of_parts++;

        if ((string::npos != max_count) && (parts.size() == max_count))
            break;

        if ((current - prev) > 0)
            parts.emplace_back(source.substr(prev, current - prev));

        prev = current + needle_len;

        if (prev >= source_len)
            break;
    }

    if (prev < source_len)
    {
        if (string::npos == max_count)
            parts.emplace_back(source.substr(prev));

        else if ((string::npos != max_count) && (parts.size() < max_count))
            parts.emplace_back(source.substr(prev));
    }

    return parts;
}

string insert_delimiters_into_string_at_appropriate_places(const string &encoded_str)
{
    string padded_encoded_str{encoded_str};
    size_t start{encoded_str.length() - 1};

    while ((start = padded_encoded_str.find_last_of("LRSN", start)) != string::npos)
    {
        switch (padded_encoded_str[start])
        {
        case 'N':
            if ((start < padded_encoded_str.length() - 1) && ('|' != padded_encoded_str[start + 1]))
                padded_encoded_str.insert(start + 1, 1, '|');
            if (0 < start - 1)
                padded_encoded_str.insert(start - 1, 1, '|');
            start--;
            break;

        case 'S':
            if ((start < padded_encoded_str.length() - 1) && ('|' != padded_encoded_str[start + 1]))
                padded_encoded_str.insert(start + 1, 1, '|');
            if (0 < start - 2)
                padded_encoded_str.insert(start - 2, 1, '|');
            start -= 2;
            break;

        case 'L':
            if ((start < padded_encoded_str.length() - 1) && ('|' != padded_encoded_str[start + 1]))
                padded_encoded_str.insert(start + 1, 1, '|');
            if (0 < start - 1)
                padded_encoded_str.insert(start - 1, 1, '|');
            start--;
            break;

        case 'R':
            if ((start < padded_encoded_str.length() - 1) && ('|' != padded_encoded_str[start + 1]))
                padded_encoded_str.insert(start + 1, 1, '|');
            if (0 < start - 1)
                padded_encoded_str.insert(start - 1, 1, '|');
            start--;
            break;

        default:
            break;
        }
    }

    return padded_encoded_str;
}

char get_next_char(const char ch)
{

    return static_cast<char>(static_cast<size_t>(ch) + 1u);
}

char get_prev_char(const char ch)
{

    return static_cast<char>(static_cast<size_t>(ch) - 1u);
}

string AlphabetRunEncryption(string str)
{
    str = trim(str);
    const string encoded_str{insert_delimiters_into_string_at_appropriate_places(str)};

    const vector<string> str_parts{split(encoded_str, "|")};

    string decoded_str{};
    char previous_simple_seq_char{};

    for (const auto &seq : str_parts)
    {
        size_t start{};

        if ((start = seq.find_first_of("LRSN", start)) != string::npos)
        {
            switch (seq[start])
            {
            case 'N':

                decoded_str.push_back(seq[start - 1]);
                previous_simple_seq_char = seq[start - 1];

                break;

            case 'S':
                if (seq[start - 2] == previous_simple_seq_char)
                {
                    decoded_str.push_back(seq[start - 1]);
                    previous_simple_seq_char = seq[start - 1];
                }
                else
                {
                    previous_simple_seq_char = seq[start - 1];
                    decoded_str.push_back(seq[start - 2]);
                    decoded_str.push_back(seq[start - 1]);
                }
                break;

            case 'L':
                if (get_next_char(seq[start - 1]) == previous_simple_seq_char)
                {
                    decoded_str.push_back(get_prev_char(seq[start - 1]));
                }
                else
                {
                    decoded_str.append({get_next_char(seq[start - 1]), get_prev_char(seq[start - 1])});
                }

                previous_simple_seq_char = get_prev_char(seq[start - 1]);
                break;

            case 'R':
                if (get_prev_char(seq[start - 1]) == previous_simple_seq_char)
                {
                    decoded_str.push_back(get_next_char(seq[start - 1]));
                }
                else
                {
                    decoded_str.append({get_prev_char(seq[start - 1]), get_next_char(seq[start - 1])});
                }

                previous_simple_seq_char = get_next_char(seq[start - 1]);
                break;

            default:
                return "not possible";
            }
        }
        else
        {
            const size_t seq_len{seq.length()};
            size_t index{};

            bool is_prev_decoded_char_seq{};

            while (index < seq_len - 1)
            {
                const char fc{seq[index]};
                const bool is_dir_forward{seq[index + 1] > seq[index]};

                for (size_t i{index + 1}; i < seq_len; i++)
                {
                    if ((seq[i] == seq[i - 1]) || (abs(seq[i] - seq[i - 1]) > 1) || (seq_len - 1 == i))
                    {
                        if (!is_prev_decoded_char_seq)
                        {
                            is_prev_decoded_char_seq = true;
                            if (is_dir_forward)
                            {
                                if (get_prev_char(fc) == previous_simple_seq_char)
                                {
                                    decoded_str.push_back(get_next_char(seq[i]));
                                    previous_simple_seq_char = get_next_char(seq[i]);
                                }
                                else
                                {
                                    decoded_str.append({get_prev_char(fc), get_next_char(seq[i])});
                                    previous_simple_seq_char = get_next_char(seq[i]);
                                }
                            }
                            else
                            {
                                if (get_next_char(fc) == previous_simple_seq_char)
                                {
                                    decoded_str.push_back(get_prev_char(seq[i]));
                                    previous_simple_seq_char = get_prev_char(seq[i]);
                                }
                                else
                                {
                                    decoded_str.append({get_next_char(fc), get_prev_char(seq[i])});
                                    previous_simple_seq_char = get_prev_char(seq[i]);
                                }
                            }
                        }
                        else
                        {
                            if (is_dir_forward)
                            {
                                if ((abs(seq[i] - seq[i - 1]) > 1))
                                {
                                    decoded_str.push_back(get_next_char(seq[i - 1]));
                                    previous_simple_seq_char = get_next_char(seq[i - 1]);
                                }
                                else
                                {
                                    decoded_str.push_back(get_next_char(seq[i]));
                                    previous_simple_seq_char = get_next_char(seq[i]);
                                }
                            }
                            else
                            {
                                if ((abs(seq[i] - seq[i - 1]) > 1))
                                {
                                    decoded_str.push_back(get_prev_char(seq[i - 1]));
                                    previous_simple_seq_char = get_prev_char(seq[i - 1]);
                                }
                                else
                                {
                                    decoded_str.push_back(get_prev_char(seq[i]));
                                    previous_simple_seq_char = get_prev_char(seq[i]);
                                }
                            }
                        }

                        index = i;
                        break;
                    }
                }
            }
        }
    }

    return decoded_str;
}

int main()
{
    // cout << AlphabetRunEncryption(move(string{gets(stdin)}));
    cout << AlphabetRunEncryption(move(string{"cdefghijklmnnmlkjihgfedcb"})) << '\n'; // expected output: "boa"
    cout << AlphabetRunEncryption(move(string{"bcdefghijklmnopqrstN"})) << '\n';      // expected output: "att"
    cout << AlphabetRunEncryption(move(string{"abSbaSaNbR"})) << '\n';                // expected output: "abaac"
    cout << AlphabetRunEncryption(move(string{"defghijklmnnmlkjihgfedeS"})) << '\n';  // expected output: "code"
    cout << AlphabetRunEncryption(move(string{"bRdR"})) << '\n';                      // expected output: "ace"
    cout << AlphabetRunEncryption(move(string{"bRcNdR"})) << '\n';                    // expected output: "acce"
    cout << AlphabetRunEncryption(move(string{"cdefghijklmnopqrstuvwxxwvusrqponmlkjihgf"})) << '\n';
    // expected output: "byte"
    cout << AlphabetRunEncryption(move(string{"baSbcdefghijklmnopqrstNtNtNtsS"})) << '\n'; // expected output: "batttts"
    cout << AlphabetRunEncryption(move(string{"baSaNabScdefghijklmnop"})) << '\n';         // expected output: "baabq"

    return 0;
}
