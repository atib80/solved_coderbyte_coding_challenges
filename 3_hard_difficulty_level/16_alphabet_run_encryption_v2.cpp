/*
Coderbyte coding challenge: Alphabet Run Encryption

Using the C++ language, have the function AlphabetRunEncryption(str) read the
str parameter being passed which will be an encrypted string and your program
should output the original decrypted string. The encryption being used is the
following: For every character i in str up to the second to last character, take
the i and i+1 characters and encode them by writing the letters of the alphabet,
in order, that range in the same direction between those chosen characters. For
example: if the original string were bo then it would be encoded as
cdefghijklmn, but if the string were boa then bo is encoded as cdefghijklmn and
oa is encoded as nmlkjihgfedcb with the final encrypted string being
cdefghijklmnnmlkjihgfedcb. So str may be something like the encrypted string
just written, and your program should decrypt it and output the original
message.

The input string will only contain lowercase characters (a...z).
There are also three important rules to this encryption based on specific
character sequences.

1) If the original string contains only one letter between two chosen
characters, as the string ac then this would be encrypted as bR with R standing
for what direction in the alphabet to go in determining the original characters.
The encrypted string bR represents ac but the encrypted string bL represents ca
(R = right, L = left).

2) If the original string contains zero letters between two chosen characters,
such as the string ab then this would be encrypted as abS, with S representing
the fact that no decryption is needed on the two letters preceding S. For
example, if the original string were aba then the encryption would be abSbaS,
but be careful because decrypting this you get abba, but the actual original
string is aba.

3) If the original string contains a repeat of letters, such as the string acc
then this would be encrypted as bRcN, with N representing the fact that no
change in characters occurred on the character preceding N. The input string
will never only be composed of repeated characters.

Sample test cases:

Input:  "bcdefghijklmnopqrstN"
Output: "att"

Input:  "abSbaSaNbR"
Output: "abaac"
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T>
class AlphabetRunEncryptionDecoder {
  static_assert(is_same<T, string>::value || is_same<T, wstring>::value ||
                    is_same<T, u16string>::value ||
                    is_same<T, u32string>::value,
                "T must be a valid C++ STL string type!");

  T enc_msg_;
  T dec_msg_;
  bool msg_decoded_;

  using char_type = typename T::value_type;

  static T decode_message(const T& str) {
    static const T needle{"LNRS"};

    T decoded_str{};
    char_type previous_simple_seq_char{};
    size_t prev_seq_start{};

    while (prev_seq_start < str.length()) {
      size_t next_seq_start{str.find_first_of(needle, prev_seq_start)};

      bool is_tail_element_processed{};

      if (T::npos != next_seq_start) {
        switch (str[next_seq_start]) {
          case static_cast<char_type>('N'):
            next_seq_start--;
            if (prev_seq_start == next_seq_start) {
              decoded_str.push_back(str[next_seq_start]);
              previous_simple_seq_char = str[next_seq_start];
              prev_seq_start = next_seq_start + 2;
              is_tail_element_processed = true;
            }
            break;

          case static_cast<char_type>('S'):
            if (prev_seq_start == next_seq_start - 2) {
              if (str[next_seq_start - 2] == previous_simple_seq_char)
                decoded_str.push_back(str[next_seq_start - 1]);
              else
                decoded_str.append(
                    {str[next_seq_start - 2], str[next_seq_start - 1]});
              previous_simple_seq_char = str[next_seq_start - 1];
              prev_seq_start = next_seq_start + 1;
              is_tail_element_processed = true;
            } else
              next_seq_start -= 2;
            break;

          case static_cast<char_type>('L'):
            next_seq_start--;
            if (prev_seq_start == next_seq_start) {
              const char_type nc{get_next_char(str[next_seq_start])};
              const char_type pc{get_prev_char(str[next_seq_start])};
              if (nc == previous_simple_seq_char) {
                decoded_str.push_back(pc);
              } else {
                decoded_str.append({nc, pc});
              }
              previous_simple_seq_char = pc;
              prev_seq_start = next_seq_start + 2;
              is_tail_element_processed = true;
            }
            break;

          case static_cast<char_type>('R'):
            next_seq_start--;
            if (prev_seq_start == next_seq_start) {
              const char_type nc{get_next_char(str[next_seq_start])};
              const char_type pc{get_prev_char(str[next_seq_start])};
              if (pc == previous_simple_seq_char) {
                decoded_str.push_back(nc);
              } else {
                decoded_str.append({pc, nc});
              }
              previous_simple_seq_char = nc;
              prev_seq_start = next_seq_start + 2;
              is_tail_element_processed = true;
            }
            break;

          default:
            break;
        }
      } else
        next_seq_start = str.length();

      if (!is_tail_element_processed) {
        size_t index{prev_seq_start};

        bool is_prev_decoded_char_seq{};

        while (index < next_seq_start - 1) {
          const char_type fc{str[index]};
          const bool is_dir_forward{str[index + 1] > str[index]};

          for (size_t i{index + 1}; i < next_seq_start; i++) {
            if (str[i] == str[i - 1] || abs(str[i] - str[i - 1]) > 1 ||
                next_seq_start - 1 == i) {
              if (!is_prev_decoded_char_seq) {
                is_prev_decoded_char_seq = true;
                if (is_dir_forward) {
                  const char_type nc{get_next_char(str[i])};
                  if (get_prev_char(fc) == previous_simple_seq_char) {
                    decoded_str.push_back(nc);
                    previous_simple_seq_char = nc;
                  } else {
                    decoded_str.append({get_prev_char(fc), nc});
                    previous_simple_seq_char = nc;
                  }
                } else {
                  const char_type pc{get_prev_char(str[i])};
                  if (get_next_char(fc) == previous_simple_seq_char) {
                    decoded_str.push_back(pc);
                    previous_simple_seq_char = pc;
                  } else {
                    decoded_str.append({get_next_char(fc), pc});
                    previous_simple_seq_char = pc;
                  }
                }
              } else {
                if (is_dir_forward) {
                  if (abs(str[i] - str[i - 1]) > 1) {
                    decoded_str.push_back(get_next_char(str[i - 1]));
                    previous_simple_seq_char = decoded_str.back();
                  } else {
                    decoded_str.push_back(get_next_char(str[i]));
                    previous_simple_seq_char = decoded_str.back();
                  }
                } else {
                  if (abs(str[i] - str[i - 1]) > 1) {
                    decoded_str.push_back(get_prev_char(str[i - 1]));
                    previous_simple_seq_char = decoded_str.back();
                  } else {
                    decoded_str.push_back(get_prev_char(str[i]));
                    previous_simple_seq_char = decoded_str.back();
                  }
                }
              }

              index = i;
              break;
            }
          }
        }

        prev_seq_start = next_seq_start;
      }
    }

    return decoded_str;
  }

 public:
  AlphabetRunEncryptionDecoder(T&& msg)
      : enc_msg_{std::forward<T>(trim(msg))}, msg_decoded_{} {}

  void set_encoded_message(T&& msg) {
    enc_msg_ = std::forward<T>(msg);
    msg_decoded_ = false;
  }

  const T& get_decoded_message() {
    if (!msg_decoded_) {
      dec_msg_ = decode_message(enc_msg_);
      msg_decoded_ = true;
    }
    return dec_msg_;
  }

  static char_type get_next_char(const char_type ch) { return ch + 1; }

  static char_type get_prev_char(const char_type ch) { return ch - 1; }

  static T trim(const T& input) {
    T output{input};
    output.erase(begin(output),
                 find_if(begin(output), end(output),
                         [](const char_type ch) { return !is_ws_char(ch); }));

    output.erase(find_if(output.rbegin(), output.rend(),
                         [](const char_type ch) { return !is_ws_char(ch); })
                     .base(),
                 end(output));

    return output;
  }

  static bool is_ws_char(const char_type ch) {
    switch (ch) {
      case static_cast<char_type>(' '):
      case static_cast<char_type>('\t'):
      case static_cast<char_type>('\n'):
      case static_cast<char_type>('\r'):
      case static_cast<char_type>('\v'):
      case static_cast<char_type>('\f'):
        return true;

      default:
        return false;
    }
  }
};

string AlphabetRunEncryption(string str) {
  AlphabetRunEncryptionDecoder<string> are_decoder{move(str)};
  return are_decoder.get_decoded_message();
}

int main() {
  // cout << AlphabetRunEncryption(move(string{gets(stdin)}));
  cout << AlphabetRunEncryption(string{"cdefghijklmnnmlkjihgfedcb"})
       << '\n';  // expected output: "boa"
  cout << AlphabetRunEncryption(string{"bcdefghijklmnopqrstN"})
       << '\n';  // expected output: "att"
  cout << AlphabetRunEncryption(string{"abSbaSaNbR"})
       << '\n';  // expected output: "abaac"
  cout << AlphabetRunEncryption(string{"defghijklmnnmlkjihgfedeS"})
       << '\n';  // expected output: "code"
  cout << AlphabetRunEncryption(string{"bRdR"})
       << '\n';  // expected output: "ace"
  cout << AlphabetRunEncryption(string{"bRcNdR"})
       << '\n';  // expected output: "acce"
  cout << AlphabetRunEncryption(
              string{"cdefghijklmnopqrstuvwxxwvusrqponmlkjihgf"})
       << '\n';
  // expected output: "byte"
  cout << AlphabetRunEncryption(string{"baSbcdefghijklmnopqrstNtNtNtsS"})
       << '\n';  // expected output: "batttts"
  cout << AlphabetRunEncryption(string{"baSaNabScdefghijklmnop"})
       << '\n';  // expected output: "baabq"

  return 0;
}
