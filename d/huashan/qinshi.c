// Room: /d/huashan/qinshi.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
int do_move(string arg);
int do_push(string arg);
int do_tiao(string arg);

void create()
{
        set("short", "寝室");
        set("long", @LONG
这里是岳不群的寝室，岳不群在江湖上人称「君子剑」，他虽为一大派掌门，
可他的卧室却布置的很简单。除了一张床，几只箱子，墙角有张化妆台，只有靠墙
一张红木书桌(desk)还显得略有气派。屋北方向有一扇窗户，侧耳倾听，山风呼啸
松涛阵阵，隐隐约约有树影婆娑掩映。
LONG
        );
        set("exits", ([ 
		"north" : __DIR__"houtang",
	]));
        set ("item_desc", ([
                "desk" : 
"这是一张很结实的红木书桌，桌面上摆着几只狼毫笔，磨了一半的墨，\n"
"还有一叠未用的白纸。\n",
	            "窗户" : 
"这是一扇小窗户，窗户外是悬崖峭壁，险峻异常，\n"
"窗户开合间山风呼啸而来，甚是猛烈。\n"
        ])  ) ;

	 set("objects",([
	 	__DIR__"obj/shengzi" : 1,
	 ]));

        set("no_clean_up", 0);
	    set("indoors", "华山" );

        set("coor/x",80);
        set("coor/y",-40);
        set("coor/z",80);
        setup();
}

void init()
{
    add_action("do_push","tui");
    add_action("do_tiao","jump");
	add_action("do_move","move");
	add_action("do_tiao","tiao");
}

int do_move(string arg)
{
	object me=this_player();
	object xin;
	if (!arg || arg!="桌子")
	{
		return notify_fail("你要移动什么东西？\n");	
	}
	if (!me->query_temp("zyy/askyue"))
	{
		return notify_fail("这是掌门的私人房间，你随便乱搬动什么东西？\n");	
	}
	xin=new("d/huashan/obj/ziyin_book");
	xin->move(this_player());	
	message_vision(YEL"$N在华山寝室中搜到一本华山秘籍。\n"NOR,me);
	return 1;

}

int do_push(string arg)
{
   object me=this_player();
   if (!arg ||arg !="窗户")
     return notify_fail("你要推什么？\n");
   if (me->query_temp("hs/tuichuang"))
   {
	   return notify_fail("你已经推开窗户了\n");
   }
   if (me->query_temp("weapon"))
      return notify_fail("你手握兵器，如何推窗户？\n");
   message_vision(HIC"\n\n$N轻轻推开窗户，山风猛烈向屋内吹来，你忍不住打了个寒颤。\n"NOR,me);
   message_vision(HIG"\n\n$N向外望去，窗下即为万丈悬崖，深不可测，隐约可见窗外有一棵千年老松长在悬崖边上。\n"NOR,me);


   //上文衔接在林家铺子遭到抢劫。。
   me->set_temp("hs/tuichuang",1);
   return 1;
}
int do_tiao(string arg)
{
   object me=this_player();
   if (!arg ||arg !="千年老松") return 0;

   if (me->query("quest/pxj/super2/pass")) 
   {
       	me->set("title",HIM"群邪辟易"NOR);
		me->set("mytitle/quest/pxjtitle",HIM"群邪辟易"NOR);
		return notify_fail("你已经解密了辟邪剑法，还往哪儿跳什么？\n");

   }
   if (!me->query_temp("hs/tuichuang"))
      return notify_fail("你拿脑袋向窗户上撞？\n");
   if (me->query_skill("dodge",1)<350) 
      return notify_fail("你的轻功太低，不足350，不怕摔死？\n");
	
   message_vision(HIC"\n\n$N轻轻一纵深，从窗户中飞身跃出,飞落到那株老松树上。\n"NOR,me);
   me->move("/d/huashan/song1");
   me->delete_temp("hs/tuichuang");
   me->set_temp("hs/tiaochuang",1);
   return 1;
}