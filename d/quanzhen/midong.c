// ȫ��� qixing-jian/lianzhen2 quest
//modifield by action@SJ 2008/9/18
#include <ansi.h>;
inherit ROOM;
inherit F_SSERVER;
void create()
{
	set("short", HIB"�ܶ�"NOR);
	set("long", @LONG
����ȫ����������Լ��ھ���ܶ�����̫������ʱ��ֱ��ȫ�������������ڴ�ס
����������һʯ������߷���һЩʯ�룬���ϵľ�Ȼ�м���С��(hole)������͸
��С��ֱ�����������С�������к��񱱶����ǵ����У����������(yanlian)��
LONG
	);
  set("item_desc", ([
        "hole": CYN"����һ�������������ⲿ��һ��С�ף����Կ�������⾰����ʱ�й���ͨ�����С�����������ҡ�\n"NOR,
	    "����":HIC"������ƺ����������½�룬�粻��ϸ�۲죬����û����ʲô�쳣��\n"NOR,
        ]) );
  set("canwu",1);
  set("exits", ([
		"up" : __DIR__"shandong",
	]));    
	setup();
}

void init()
{
	object me=this_player();
	if (me->query_temp("quest/qixing/asked")) 
	{
		add_action("do_yanlian", "yanlian");
		//me->delete_temp("quest/qixing/asked");
		me->set_temp("quest/qixing/enter",1);
		//load_object("d/quanzhen/obj/bowl1")->move(environment(me));
	}
	if (!me->query_temp("quest/qixing/asked")||me->query("qixing/pass")) 
	   me->move("/d/quanzhen/shandong");
}


int do_yanlian(string arg)
{
	object me;
	me = this_player();

	if( !me||!living(me) ) return 0;
	if( arg == ""|| !arg) return notify_fail("��������ʲô���ݣ�\n");
    if( me->query("family/family_name") !="ȫ���" )
	{
		me->move("/d/quanzhen/shandong");
		return notify_fail("��Ȼڤڤ����һ���������һ����������ô�����ģ�����\n");
	}
	if( (int)me->query_skill("quanzhen-jianfa", 1) < 450 )
		return notify_fail("���ȫ�潣���ȼ����㣬��ô��Ҳû���á�\n");
    if( (int)me->query_skill("xiantian-gong", 1) < 450 )
		return notify_fail("������칦�ȼ����㣬��ô��Ҳû���á�\n");
	if( me->is_busy() || me->is_fighting() )
		return notify_fail("����æ���ء�\n");
	
  	if( time()-me->query("quest/qz/qzjf/qixing/time")< 86400)
		return notify_fail("����äĿϹ��������ģ��㻹��ȥ��Ϣһ�°ɡ�\n");
   	
	if(me->query("quest/qz/qzjf/qixing/pass"))
	{
		
		me->set("title",HIG"��"HIC"��"HIR"��"HIY"��"HIM"��"HIC"����"NOR);
		me->set("mytitle/quest/qzqixingtitle",HIG"��"HIC"��"HIR"��"HIY"��"HIM"��"HIC"����"NOR);
		return notify_fail("��Ҫ�˷�ʱ���ˣ����Ѿ�����ȫ�潣���������ڡ�\n");
	}
	
	//if(me->query("qixing/time")< 86400)
		//return notify_fail("������̫������\n");	
	
	if( arg == "���Ǿ���"|| arg == "qixing") {
	
			message_vision("$N��������С����������Ĺ��ߣ����𱱶����ǽ����Ǿ���������ʽ����\n", me);
			me->set("qixing/time",time());
            me->set("qixing/combat_exp",me->query("combat_exp"));
		    //remove_call_out("canwu");
			me->start_busy(999);
            call_out("canwu", 1, me);  
            return 1;
         }  
      return notify_fail("ʲô��\n");
         
} 							
void canwu(object me)
{
  if(!me) return;  
    remove_call_out("thinking");
    call_out("thinking", 2, me); 

	this_object()->add("canwu",1);

    message_vision(HIR"����Ŵ�С���������Ĺ��ߣ������ű������ǵĲ���.........\n"NOR,me);
    //me->start_busy(2);
}

int thinking(object me, object ob)
{
	int j,i,total;
	//object bowl;
	if(!me) return 0;
	//bowl=present("posun shuiwan",environment(me));
    if(me->query_temp("lianzhen_thinking")<(6+random(3)))
	{
		me->add_temp("lianzhen_thinking",1);
        if(random(2)) tell_object(me,WHT"\n�㰴�չ����ս�����·����ʽ,��������һ�飬�㷢����Ľ���Խ��Խ��...\n"NOR);
        else tell_object(me,HIG"\n\nͻȻ�䣬���ƺ�ץ����ʲô����ʱ�ܶ��н����ҫ�����ƺ��о����˱��������б仯...\n"NOR);
	    remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
       me->delete_temp("lianzhen_thinking");      

	//  total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      
	  j = 22;

      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  18;
      if(me->query("buyvip"))     j =  10;
      i=random(j);

      if (i <3 
		 && random(me->query("int")) > 40 
	     && me->query("kar")<31
		 && random(me->query("kar"))>26)
	  {
   
       tell_object(me,HIG"\n�㷢�����Ѿ���ȫ������ǽ�ڵ���ʽ����ʽ���������ױ�֮��������ʯ�ҳ�����������\n"NOR);
       message_vision(HIG"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
       me->set("quest/qz/qzjf/qixing/pass",1);
       me->delete_temp("quest/qixing");
	   me->set("title",HIG"��"HIC"��"HIR"��"HIY"��"HIM"��"HIC"����"NOR);
	   me->set("mytitle/quest/qzqixingtitle",HIG"��"HIC"��"HIR"��"HIY"��"HIM"��"HIC"����"NOR);
       message_vision(HIC"\n������ս����Ĺ��ߣ��������������Ǿ������ľ������ڡ���\n"NOR,me);   
       me->delete_temp("quest");
	   log_file("quest/qixing", sprintf("%s(%s) ʧ��%d�γɹ��⿪���Ǿ���������Դ��%d�����飺%d��\n", me->name(1),me->query("id"), me->query("quest/qz/qzjf/qixing/fail"),me->query("kar"),me->query("combat_exp")) );	   
	  
	 }
    else
    {
       tell_object(me,HIG"\n���Ժ����ƺ�ץס��ʲô��������Ȼ����Ҫ�졣\n"NOR);
       message_vision(HIC"\n$Nҡ��ҡͷ�������������Ǻ����ѵġ���˵�գ������̾�˿�����\n"NOR,me); 
       me->add("quest/qz/qzjf/qixing/fail",1);
       me->set("quest/qz/qzjf/qixing/time",time());
       me->move("d/quanzhen/shandong");
	   me->delete_temp("quest");
	   me->delete_temp("quest/qixing");
	   
	   log_file("quest/qixing", sprintf("%s(%s) �����Ǿ�����ʧ�ܣ�%d�Ρ���Դ��%d�����飺%d��\n", me->name(1),me->query("id"), me->query("quest/qz/qzjf/qixing/fail"),me->query("kar"),me->query("combat_exp")) );
    }
	me->start_busy(-1);
  }
  return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_temp("quest/qixing/enter") && dir == "up")
			me->delete_temp("quest");
        return ::valid_leave(me, dir);
}
