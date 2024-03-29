/*! @file modAlphaCipher.cpp
 * @author Козин А. В.
 * @version 1.0.0
 * @date 13.06.2019
 * @brief Заголовочный файл для модуля modAlphaCipher.cpp
 */
#include "modAlphaCipher.h"

modAlphaCipher::modAlphaCipher(const std::string& skey)
	/** 
* @brief Перевод из кодировки UTF-32 в UTF-8 
* @param [in] s Строка в кодировке UTF-32 
* @return Строка в кодировке UTF-8 
*/ 
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	std::wstring wskey = towstr(skey);
	key = convert(wskey);
}
 /**
 * @brief Зашифровывание
 * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
 * Строчные символы автоматически преобразуются к
прописным.
 * Все не-буквы удаляются
 * @return Зашифрованная строка
 * @throw cipher_error, если текст пустой
 */
std::string modAlphaCipher::encrypt(const std::string&
                                    open_text)

{
	std::wstring open_wtext = towstr (open_text);
	std::vector<int> work = convert(open_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) %
		          alphaNum.size();
	}
	return convert(work);
}
									 /**
	/** 
* @brief Расшифровывание 
* @param [in] cipher_text Зашифрованный текст в 
кодировке UTF-8. Не должен быть пустой строкой. 
* Не должен содержать строчные символы и небуквы. 
* @return Расифрованная строка в кодировке UTF-8 
* @throw cipher_error текст пустой 
*/ 
std::string modAlphaCipher::decrypt(const std::string&
                                    cipher_text)
{
	std::wstring cipher_wtext = towstr (cipher_text);
	std::vector<int> work = convert(cipher_wtext);
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i %
		           key.size()]) % alphaNum.size();
	}
	return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const
        std::wstring& ws)
{
	std::vector<int> result;
	for(auto wc:ws) {
		result.push_back(alphaNum[wc]);
	}
	return result;
}
inline std::string modAlphaCipher::convert(const
        std::vector<int>& v)
{
	std::wstring wresult;
	for(auto i:v) {
		wresult.push_back(numAlpha[i]);
	}
	std::string result = fromwstr(wresult);
	return result;
}
std::wstring modAlphaCipher::towstr(const std::string& s)
{
	std::locale loc("ru_RU.UTF-8");
	std::wstring_convert<std::codecvt_utf8<wchar_t>,
	    wchar_t> codec;
	std::wstring ws = codec.from_bytes(s);
	return ws;
}
std::string modAlphaCipher::fromwstr(const std::wstring&
                                     ws)
{
	std::locale loc("ru_RU.UTF-8");
	std::wstring_convert<std::codecvt_utf8<wchar_t>,
	    wchar_t> codec;
	std::string s = codec.to_bytes(ws);
	return s;
}