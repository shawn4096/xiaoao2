// Room: /d/huashan/yunu.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
int yue_say(object me,object feng,object cheng,object cong,object yue,object ning);
void create()
{
	set("short", "��Ů��");
	set("long", @LONG
�����ǻ�ɽ���з壬��Ů�塣��Ů�������Ϊƽ�������������ķ��ǰ���
���������Ϻպ������Ļ�ɽ���ɾ��ڴ˴�����������СС������Ǿ�����Ů
���ˡ�����ϡϡ������ʮ���䷿�ӣ������ǻ�ɽ�ɵĵط��������ο���ñ���
��ȥ��
LONG
	);
	set("exits", ([
		"northdown" : __DIR__"zhenyue",
		"northwest" : __DIR__"xiaolu1",
		"east" : __DIR__"yunuci",
		"south" : __DIR__"shanlu1",
		"west" : __DIR__"pubu",
	]));
	set("objects", ([
		NPC_D("youke") : 1,
		NPC_D("caiyaoren") : 1,
	]));
	set("outdoors", "��ɽ" );
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="south" ){
        if(me->query("can_ride")) {  return 0;  }

	    if(me->query_temp("ride_horse"))
		return notify_fail("��λ" + RANK_D->query_respect(me) + "�������������ٽ�ȥ�ɣ�\n");
        }
        return ::valid_leave(me, dir);
}

void init()
{
        object me,feng,cheng;
		object cong,yue,ning;
               
        me = this_player();
      
	 
       if (me->query_temp("jianzong/asklu")){
		     tell_object(environment(me),HIC"�ⲻƽ����������Ⱥ��������ʦ����ʹ��ı��ƣ���ռ�˻�ɽһ�ɣ���ʾ��ʣ����տɵ����㡣\n"
		                 +"��Ҳ��Ҫ���㡰��ʦ�֡����ߺߣ�����֮�������ڵ��°������ٽ�һ����Ҳ����ö����ء�\n"NOR);
              message_vision(HIY"ͻȻ����Ӱһ����������Ʈ��һ��������������˸�����������Ѻ�³���ٶ���һ������������������\n"
		                 +"���������ν������ܣ�������һ���ǳɣ���ʽ�ָ�����֮�������Ǽ��죬������������ȴ������죬����������\n"NOR,me);
		  if (!present("feng buping",environment(me)))
          {
			feng=new("/d/huashan/npc/sword/fengbuping.c");
			feng->move("/d/huashan/yunu");
			
          }else feng=present("feng buping",environment(me));
		 if (!present("chong buqi",environment(me)))
          {
			cong=new("/d/huashan/npc/sword/chongbuqi.c");
			cong->move("/d/huashan/yunu");
			cong->set_temp("jiali",60);
         }else cong=present("chong buqi",environment(me));
        if (!present("cheng buyu",environment(me)))
         {
			cheng=new("/d/huashan/npc/sword/chengbuyu.c");
			cheng->move("/d/huashan/yunu");
         }else cheng=present("cheng buyu",environment(me));
		if (!present("yue buqun",environment(me)))
         {
			yue=new("/d/huashan/npc/yuebuqun.c");
			yue->move("/d/huashan/yunu");
			//yue->add_temp("apply/attack",-100);
			//yue->add_temp("apply/damage",-70);
         }else yue=present("yue buqun",environment(me));
		 if (!present("ning zhongze",environment(me)))
         {
			ning=new("/d/huashan/npc/ningzhongze.c");
			ning->move("/d/huashan/yunu");
			ning->set("jiali",50);
         }else ning=present("ning zhongze",environment(me));
		 
		 cong->fight_ob(ning);
		 ning->fight_ob(cong);
		 yue->fight_ob(cheng);
		 cheng->fight_ob(yue);
		 
		//yue->command("say haha");
		call_out("yue_say", 7, me,feng,cheng,cong,yue,ning);
		return;
	} 
}

int yue_say(object me,object feng,object cheng,object cong,object yue,object ning)
{  
	
	message_vision(HIY"\n\n\n����Ⱥ������������Լ��ˣ��л�����������˵���αض��֣��������߹�����˳�ִ��͵�ŵ���߳������\n"
		                            +"һ��һ�������Բ�������������������ѹס���Բ����˾��ڱۣ�������̧�����Ͼ�Ȼ��˿����������һ��\n"
									+"��������������ȺЦ����������������ͬ����֦�������Լ���һ�㣬��ʦ�ֲ��غ�����һ���ʶ����\n"
									NOR,me);
	message_vision(HIR"\n\n\n$N�ۼ��Է��˶࣬����һս��Ȼ��ʦ������Ⱥǿ��ѹ�����������ⲻƽ��û�ж��֣��в�֪��\n"+
		               "�������˵�����ʵ���������Աߵ���ɽ����ɽ���ɵ�����Ҳ�������Թۣ���֪�����ǵ�������ͼ��\n"NOR,me);
    if (objectp(feng)) destruct(feng);
	if (objectp(cheng)) destruct(cheng);
	if (objectp(cong)) destruct(cong);
	if (objectp(yue))  destruct(yue);
	if (objectp(ning)) destruct(ning);
	call_out("leave_all",5,me);
	return 1;

}
int leave_all(object me)
{
	
	tell_object(environment(me),CYN"\n\n���ۼ�����½����ɢ����������Ⱥ���ἰ�Ŀֲ����飬���м�Ϊ������\n"
	                               +"���ڵĽ���ȷʵϬ�����Ӳ�����ʦ��һս���Ѿ��������ߣ��⽣�ڵĽ��������쳣��\n"
								   +"�Լ���ʦ�����ڻ��ǽ����⽫һ����Ϊ���ѵ�ѡ��\n"NOR);
    me->delete_temp("jianzong/asklu");
	me->set_temp("jianzong/bijian",1);
	return 1;


}