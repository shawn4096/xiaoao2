// By Spiderii@yt bt物品
#include <ansi.h>
#define BOOK    "/clone/gift/book"      //书
#define MIC     "/clone/gift/danwan"    //药
#define MON     "/clone/gift/money"     //钱
#define JADE    "/clone/zhiye/othermaterial" //玉
#define MIJI    "/u/yueying/jinshe/obj/jszf-book"//秘籍
inherit SPEC;
void create()
{
	set_name(HIW"神秘宝盒"NOR, ({ "box","baohe" }) );
	set_weight(10);
	set("unit", "个");
	set("long", "一个神秘的五彩盒子。\n是传说中天神管理员(action)遗落凡间的宝物，它是能给人们带来幸运和厄运的魔力之盒。\n是不是经不起它的诱惑呢，那就快打开（open）它吧。。。\n");
	set("value", 0);
	set("material", "wood");
	set("no_drop", "这样贵重的东西怎么能随便乱丢呢。\n");
	set("no_get", "这样东西不能离开那儿。\n");
	set_weight(100);
	set("value",3000000);
	set("treasure",1);
	set("degree",1);
	set("flag","spec/baohe");
	set("desc","据说打开盒子会有宝玉出现。");
	set("credit",150);    

	setup();
}
void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{        
	object me = this_player();
	object obj;
	string str = "";
	int i = random(4);

	if(arg!="box" && arg!="baohe")
		return notify_fail("你要打开什么?\n");

	switch(i) {
		case 0:         
			obj = new (BOOK);
			str = "书";  
			break;
		case 1: 
			obj = new (MIC);
			if (random(me->query_kar()) > 29) {
				obj->set("secret_obj",1);
				str = "极品";
			}
			str += "药";     
			break;
		case 2:         
			obj = new (MON);
			str = "钱"; 
			break;
		case 3:
			obj = new (MIJI);
			str = "秘籍";
			break;
		default:return 1;
	}
	obj->move(this_player());
	message_vision(HIW"$N从宝盒中得到了一"+obj->query("unit")+obj->name()+"。\n\n"NOR,me); 
	destruct(this_object());
	return 1;
}

