// wdroad8.c 黄土路
// By Spdierii@ty 加入yttlg quest
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "山脚下");
	set("long", @LONG
这里是武当山脚下，两旁是阴森森的树林。西边是一座高山, 东南方是一
茶亭。所谓偷得浮生半日闲! 没有比这更好的歇脚方法了。
LONG
	);
        set("outdoors","武当");

	set("exits", ([
		"east" : "/d/group/entry/wdroad7",
                "southeast" :"/d/wudang/chating",
                "west" : "/d/wudang/xuanyue",
	]));

	set("objects", ([
                "/d/wudang/npc/yetu" : 2 
	]));
        setup();
}

int valid_leave(object me, string dir)
 {
     if ( me->query_temp("quest/yttlg/asksong"))
             return notify_fail("你还是先安心解谜吧！！\n");
     return ::valid_leave(me, dir);
 }

void init()
{
  object me;
  me = this_player();
  if (me->query_temp("quest/yttlg/asksong"))
  {
     tell_object(me,HIW"你突然见得有队镖车在路边休息,趟子手中高举着跃鲤镖旗。”\n"NOR); 
     tell_object(me,HIW"车旁站立两人,似乎在争论着什么,原来是临安府龙门镖局的镖车。\n"NOR);       
     remove_call_out("story");
     call_out("story", 3, me);      
     write(CYN"\n你不由感到十分好奇，你停了下来，静静倾听。\n"NOR);
}
}
void story(object me)
{
  if(!me) return;

   tell_object(me,YEL"\n你听到“武当弟子”、“这番羞辱”，似乎与武当派有些关联，却听不清楚具体在说什么，你不由好奇心起。\n"NOR); 
   tell_object(me,YEL"\n你走上前去,双手抱拳,问道:贵局可是临安府龙门镖局么?请问几位高姓大名？贵局都总镖头可好。\n"NOR);
   tell_object(me,YEL"\n其中一人纵马上前，道：“在下便是都大锦，阁下是.....?\n"NOR); 
   tell_object(me,YEL"\n你微微一笑,道:武当后学之辈,各位来到武当，怎地过门不入？\n"NOR);
   tell_object(me,YEL"\n今日正是家师九十寿诞之期，倘若不耽误各位要事，便请上山去喝杯寿酒如何。\n"NOR); 
   tell_object(me,YEL"\n都大锦微怒道:若令师兄也如阁下这般爱朋友，我们这时早在武当山上了。\n"NOR);
   remove_call_out("story1");
   call_out("story1", 10, me);      
   write(CYN"\n你觉得都大锦话中有话,顿觉奇怪。\n"NOR);


}
void story1(object me)
{
  if(!me) return;

   tell_object(me,YEL"\n你闻言,奇道:怎么？总镖头见过我师兄了？是哪一个？。\n"NOR); 
   tell_object(me,YEL"\n都大锦道：在下今日运气不差，一日之间，武当七侠人人都会遍了。\n"NOR);
   tell_object(me,YEL"\n你不由“啊”的一声，呆了一呆，问道：我俞三哥你也见到了么？\n"NOR); 
   tell_object(me,YEL"\n都大锦道：俞岱岩俞三侠么？我可不知哪一位是俞三侠。只是六个人一起见了，俞三侠总也在内。\n"NOR);
   tell_object(me,YEL"\n你摇头道：那决计不会，宋师哥他们今日一直在山上紫霄宫侍奉师父，没下山一步。\n"NOR); 
   tell_object(me,YEL"\n你接着说道:师父和宋师哥见俞三哥过午还不上山，命小弟下山等候，怎地都镖头会见到宋师哥他们。\n"NOR);
   remove_call_out("story2");
   call_out("story2", 10, me);      
   write(CYN"\n你似乎觉得事情有些蹊跷。\n"NOR);


}
void story2(object me)
{
  if(!me) return;
   tell_object(me,YEL"\n都大锦道：那位脸颊上生了一颗大黑痣，痣上有三茎长毛的，是宋大侠呢？还是俞二侠？\n"NOR);
   tell_object(me,YEL"\n你一楞，道：我师兄弟之中，并无一人颊上有痣，痣上生毛。\n"NOR); 
   tell_object(me,YEL"\n都大锦听了这几句话，一股凉气从心底直冒上来，说道：那六人自称是武当六侠，既在武当山下现身，其中又有两个是黄冠道人，我们自然…。\n"NOR);
   tell_object(me,YEL"\n你插口道：我师父虽是道人，但他所收的却都是俗家弟子。那六人自称是‘武当六侠’么？\n"NOR); 
   tell_object(me,YEL"\n都大锦隔了半晌，才道：“如此说来，这六人只怕不怀好意，咱们快追！。\n"NOR);
   remove_call_out("story3");
   call_out("story3", 10, me);      
   write(CYN"\n你渐觉事情有些不妙。\n"NOR);

}
void story3(object me)
{
  if(!me) return;
   tell_object(me,YEL"\n你不紧不慢的说道:那六人混冒姓名，都兄便由得他们去罢！\n"NOR);
   tell_object(me,YEL"\n都大锦气喘喘的道:可是那人呢？俺受人重嘱，要将那人送上武当山来交给张真人。\n"NOR); 
   tell_object(me,YEL"\n都大锦气喘喘的道:这六人假冒姓名，接了那个人去，只怕……只怕事情要糟………。\n"NOR);
   tell_object(me,YEL"\n你听了不由奇道：都兄送谁来给我师父？那六人接了谁去？\n"NOR); 
   tell_object(me,YEL"\n都大锦催马急奔，一面将如何受人嘱托送一个身受重伤之人来到武当山之事说了！。\n"NOR);
   remove_call_out("story4");
   call_out("story4", 10, me);      
   write(CYN"\n你听后更觉诧异。\n"NOR);

}
void story4(object me)
{
  if(!me) return;
   tell_object(me,YEL"\n你不由问道:那受伤之人是甚么姓名？年貌如何？\n"NOR);
   tell_object(me,YEL"\n都大锦道：也不知他姓甚名谁，他伤得不会说话，不能动弹，只剩下一口气了。这人约莫三十左右年纪。\n"NOR); 
   tell_object(me,YEL"\n都大锦接着说出了那人的模样。\n"NOR);
   tell_object(me,YEL"\n你大吃一惊，叫道：“这……这便是我俞三哥啊。\n"NOR); 
   tell_object(me,YEL"\n你急道：我俞三哥怎会受伤？对头是谁？是何人请都大哥送他前来？\n"NOR);
   tell_object(me,YEL"\n对这三句问话，都大锦却是一句也答不上来。\n"NOR);
   tell_object(me,YEL"\n你更是邹起眉头,又问：“接了我俞三哥去的人是怎生模样？\n"NOR); 
   tell_object(me,YEL"\n都大锦旁边的史镖头口齿灵便，抢着说了。\n"NOR);
   tell_object(me,YEL"\n你听得师哥身受重伤，又落入了不明来历之人手中，不由的心急如焚。\n"NOR); 
   tell_object(me,YEL"\n你急道：小弟先赶一步。说罢微一抱拳,急奔而去!\n"NOR);
   me->move("/d/wudang/shiqizhen");

}


