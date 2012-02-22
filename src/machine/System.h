/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

namespace machine {

class System {
public:
	typedef Object* (Getter)(System& self, ObjectHeap& heap);
	typedef void (Setter)(System& self, ObjectHeap& heap, Object* const obj);
	typedef Object* (Method)(System& self, ObjectHeap& heap, Machine& machine);
private:
	std::map<std::string, Getter> getterList();
	std::map<std::string, Setter> setterList();
	nekomata::Adapter& adapter;
public:
	System(nekomata::Adapter& adapter);
	virtual ~System();
	bool hasSystemProperty(const std::string& key);
	Object* getProperty(const std::string& key, ObjectHeap& heap);
	void setProperty(const std::string& key, ObjectHeap& heap, Object* const obj);
public:
	unsigned int getCommentColor();
	void setCommentColor(unsigned int color);

	std::string getCommentPlace();
	void setCommentPlace(const std::string& place);

	std::string getCommentSize();
	void setCommentSize(const std::string& size);

	bool getCommentInvisible();
	void setCommentInvisible(bool commentInvisible);

	bool getCommentReverse();
	void setCommentReverse(bool commentReverse);

	bool getDefaultSage();
	void setDefaultSage(bool defaultSage);

	bool getPostDisabled();
	void setPostDisabled(bool postDisabled);

	bool getSeekDisabled();
	void setSeekDisabled(bool seekDisabled);

	bool getIsLoaded();
	void setIsLoaded(bool isLoaded);

	bool getIsWide();
	void setIsWide(bool isWide);

	std::string getLastVideo();
	void setLastVideo(const std::string& lastVideo);

public:
	static Object* __getter__commentColor(System& self, ObjectHeap& heap);
	static void __setter__commentColor(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentPlace(System& self, ObjectHeap& heap);
	static void __setter__commentPlace(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentSize(System& self, ObjectHeap& heap);
	static void __setter__commentSize(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentInvisible(System& self, ObjectHeap& heap);
	static void __setter__commentInvisible(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentReverse(System& self, ObjectHeap& heap);
	static void __setter__commentReverse(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__defaultSage(System& self, ObjectHeap& heap);
	static void __setter__defaultSage(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__postDisabled(System& self, ObjectHeap& heap);
	static void __setter__postDisabled(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__seekDisabled(System& self, ObjectHeap& heap);
	static void __setter__seekDisabled(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isLoaded(System& self, ObjectHeap& heap);
	static void __setter__isLoaded(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isWide(System& self, ObjectHeap& heap);
	static void __setter__isWide(System& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__lastVideo(System& self, ObjectHeap& heap);
	static void __setter__lastVideo(System& self, ObjectHeap& heap, Object* const obj);
};

} /* namespace machine */
#endif /* SYSTEM_H_ */
