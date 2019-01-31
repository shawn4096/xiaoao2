// /area/jiangbei/wudang/jindian.c ���
// By River@SJ

inherit ROOM;
#include <ansi.h>
int do_guanmo(string arg);

void create()
{
        set("short", HIY"���"NOR);
        set("long", @LONG
���������嶥�ˣ����䵱ɽ��������Ҳ���䵱�����ڻ��ҷ���������
��ʢ�Ľ����ͭ���̽�Ľ��Ϊ�����е�ʽ��ľ�ṹ���������̽�ͺĻƽ�ǧ
�������䵱ɽ�ȼ���ߵĹŽ������������������Ϊ���䣬�����ϵ����Ŷ
�ʼ������������������Ƕ��ţ����Ƿɾ٣����������������������
�������������˲�����ǣ�ͭ������Щ�����������ۣ���Ȼ�������ڴ˴���
����
LONG
        );

        set("exits", ([
                "east" : __DIR__"taihe",
        ]));

        set("no_clean_up", 0);

        set("objects",([
                __DIR__"npc/jxk" : 1,
        ]));

        setup();
}
void init()
{

	add_action("do_guanmo","guanmo");

}

int do_guanmo(string arg)
{
	object me=this_player();
	if (!arg || arg!="����") return notify_fail("��Ҫ��Ħʲô��\n");
	if (me->query("family/family_name")!="�䵱��")
		return notify_fail("�㲻���䵱�ɵ��ӣ�������ʲô�ŵ���!\n");
	if (me->query_skill("taiji-jian",1)<350)
	{
		return notify_fail("���̫�����ȼ�̫�ͣ�����350��������������µĽ��۰��⣡\n");
	}
	if (me->query_skill("yinyun-ziqi",1)<350)
	{
		return notify_fail("����������ȼ�̫�ͣ�����350��������������µĽ��۰��⣡\n");
	}
	if (time()-me->query("quest/wd/tjj/sanhuan/time")<86400)
	{
		return notify_fail("������Ҳ̫�ڿ���Ү��\n");
	}
	if (me->query("quest/wd/tjj/sanhuan/pass"))
	{
		return notify_fail("���Ѿ�����͸���⽣�۵İ��⣡\n");
	}
	message_vision(HIC"$N��ϥ������ƽ�ľ�����������������������ʼ���������뵽һ�����µľ���֮�С�!\n"NOR,me);
	message_vision(HIC"���ľ���ˮ֮����$Ņ��ͷ����̧ͷ������ͭ��֮�ϵĽ��ۣ���Ȼ�߲�½�룬��һ��ȴ֪���䵱������Ϊ!\n"NOR,me);
	message_vision(HIC"$N���в��죬���Ǻε����Ĺ�������������ͭ����������˽���!\n"NOR,me);
	message_vision(HIC"��Ȼ��$N������ͭ��ǰ�漸��������Ȼ���������µ���ʽ�����������������ȴ���������������µĽ���!\n"NOR,me);
	message_vision(HIC"�����н���Ϊ�λ�����˰����Ȼ�ν���һ��$N��˼������⣬�����˼֮��!\n"NOR,me);
	me->set("quest/wd/tjj/sanhuan/time",time());
	me->start_busy(999);
	call_out("think_jianhen",1,me);
	
	return 1;
}

int think_jianhen(object me)
{
	int i,j;
	if(!me) return 0;
	
	if(me->query_temp("sanhuan/ask")<(10+random(3)))
    { 
	  me->add_temp("sanhuan/ask",1);
      if(random(2)) tell_object(me,HIG"\n������۲�ͭ���ϵĽ��ۣ���Ħ��ͭ���ϵ�һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬������һ��������������ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("think_jianhen");
	  call_out("think_jianhen",3+random(1), me);
	}
   else
   {  
	  me->delete_temp("sanhuan/ask");
      j = 20;
      if(me->query("m-card-vip")) j =  17;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  i=random(j);
 
 
     if(i=5 && random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n�㰴��ͭ���ϵĽ�����������̫�����������µ����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"��Ȼ��������Х��˲����������̫�����������º�������֮��Ĺ�ϵ��˳��ʩչ������\n"NOR);
		tell_object(me, HIW"����������ˮ������ͨ�\n"NOR);
		tell_object(me,HIY"\n��ϲ�㣡����ǧ����࣬���ڵó���Ը�������������ڻ��ͨ��\n"NOR);
     
		me->set("quest/wd/tjj/sanhuan/pass",1);
		
		me->start_busy(1);
		log_file("quest/tjjsanhuan", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������������µľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/wd/tjj/sanhuan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/wd/tjj/sanhuan/fail",1);
		me->set("quest/wd/tjj/sanhuan/time",time());
		command("buddha ");
		tell_object(me,HIY"�����ͭ���Ͻ��۵�·������Ȼ֪������̫��������������ʽ�����Ƕ����е���������ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HIG"�������������ؼ�ʧ�ܡ�\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/tjjsanhuan", sprintf("%8s(%8s) ̫�����������½���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/wd/tjj/sanhuan/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }



}