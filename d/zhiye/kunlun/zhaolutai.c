// jingshenfeng.c �����

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short","��¶̨"NOR);
	set("long",@long
����������ɽ����һ����ƽ̨��ͻأ��б����գ��ߵ����һ������
ɽ��������ӳ�����ɵ��䡣�����ƾ����棬��ȴ˿���о�����һ˿�ķ�����
ɽ���类��һ���п�������ƽ��������¶̨���������������پ�����Ȼ����
���������̻���ɽǰ�������±�����һʯ�壬���ǹ⻬��
long);

        set("objects",([
          //CLASS_D("kunlun")+ "/hezudao" : 1,
        ]));

        set("exits", ([
              "south" : __DIR__"jingshenfeng",
        ]));
	set("outdoors", "����");
	setup();
}
void init()
{

	if (this_player()->query_temp("hundun/askhe",1))
	{
		message_vision(HIC"$N������ǰһƬ��������Ȼ����һ���˼������ĳ�������\n"NOR,this_player());
		add_action("do_guanwu","guanwu");
		add_action("do_sit","sit");

	}else
	{
		message_vision(HIY"$NԽ��Խ��Ϳ����Ȼ�����˻�����\n"NOR,this_player());
		this_player()->move("d/kunlun/jingshenfeng");
	}

}
int do_sit(string arg)
{
	object me=this_player();
	
	if (me->query_temp("quest/kl/lyj/hundun/pass"))
	{
		return notify_fail("���زؽ��⣬����ɽ�ƴ����Ĺַ�����ϰ��Ϊ������Ȼ������\n");
	}
	if (time()-me->query("quest/kl/lyj/hundun/time")<86400)
	{
		me->move("d/kunlun/jingshenfeng");
		return notify_fail("���������Ƶ�������书���ˣ�\n");
	}
	if (me->query_temp("hundun/sit")||!me->query_temp("hundun/askhe"))
	{
		me->start_busy(1);
		return notify_fail("��ɽ���ȣ�ɽ���Х�������ƾ����棬����ľ�������⡣\n");

	}
	if (me->is_busy())
	{

		return notify_fail("��������æµ�С�\n");
	}
	if (!arg||arg!="ʯ��")
	{
		return notify_fail("��Ҫ���Ƕ���");
	}
	message_vision("$N����ʯ���ϣ��������죬����һ�ֿ���״̬��\n",me);
	me->start_busy(999);
	
	call_out("thinking",1,me);
	return 1;

}
int thinking(object me)
{
  int i,j,k;
  if(!me) return 0;
	
  if(me->query_temp("liangyi/hundun")<(10+random(10)))
    { 
	  me->add_temp("liangyi/hundun",1);
      if(random(5)) tell_object(me,HIW"\n��������������Ȼ��Ʈ��Ʈȥ.\n"NOR);
             else {
				 tell_object(me,HIY"\nͻȻ�䣬һ��ɽ�紵���������ƹ���������˲����������ɽʯ֮�䣬\n"NOR);
				 tell_object(me,HIB"\n��·�������һ����޻�֮�У��������У���ؼ��ȣ�������\n"NOR);
				 tell_object(me,HIB"\n�����о������������ż����ںϵ�����֮�����ǻ���Ī�����������\n"NOR);
				 me->add_temp("liangyi/guanyun",1);
				 }
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liangyi/hundun");
      j = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
	  i= random(i);
	  j=random(me->query("int"));
	  k=random(me->query("kar"));
 
    if(i<4 
		&& j>=40
		&& k>=26
		&& me->query_temp("liangyi/guanyun"))
	 {
		tell_object(me,HIG"\n�㰴�պ������ָ�㣬�Ի��罣�������������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"\n��һ����е�ɽ�紵��������ǰ�ǹ�ɽ�����������ϣ���о��Լ����紦��"+
							"һƬ�������У�ǰ�����Ҳ���ҡ�Σ�����ɽ����ң�Ҫ����̧�������������д󾪡�\n"+
							"���в����ͽ�����ɽ�·�����ǣ�\n"NOR);
		tell_object(me, HIB"\n���ڴ�ʱ��������һƬ���������Ǻ�����Ľ̵�����ס�Ĺأ��Կ����Ź��������"+
							"��Ȼ����������ʧ������ȴ������ĥ���е���ζ��\n"+
							"������겻����֮�ʣ������к�Ȼ������������ʱ�������������Ƶ�ԭ��\n"NOR);
		tell_object(me,HIY"\n\n\n��ϲ��������ǧ���ڿ࣬���ڵó���Ը�������罣�������ڻ��ͨ��\n"NOR);
       
		me->set("quest/kl/lyj/hundun/pass",1);
		me->set("title",HIG"���ǽ�������洫"NOR);
		me->set("mytitle/quest/lyjtitle",HIG"���ǽ�������洫"NOR);
		me->start_busy(1);
		log_file("quest/klhundun", sprintf("%8s(%8s) ʧ��%d�κ󣬳���������罣���ľ�����iȡֵ��%d|�������jȡֵ��%d|�����Դkȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/kl/lyj/hundun/fail"),i,j,k,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/kl/lyj/hudndun/fail",1);
		me->set("quest/kl/lyj/hundun/time",time());
		tell_object(me,HIY"\n\n��Ȼ��һ��ַ紵��������������⾳��ϣ������ǰ��յ�վ��������\n\n"NOR);

		tell_object(me,HIY"\n\n��Ȼ���ܵ��˻��罣���İ��أ����Ƕ����ž�����������ȫȻ����Ҫ�졣\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("hundun");
		me->delete_temp("liangyi");
		log_file("quest/klhundun", sprintf("%8s(%8s) ���罣������ʧ��%d�Ρ�iȡֵ��%d|�������jȡֵ��%d|�����Դkȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/kl/lyj/hundun/fail"),i,j,k,me->query("combat_exp")) );
	  }
    	return 1;
  }



}
