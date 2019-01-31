// Room: /d/shaolin/cjlou1.c
// Date: YZC 96/01/19
#include <ansi.h>
inherit ROOM;
string look_tjing();
int do_dian(string arg);
int yjj_wait1(object me);
int yjj_fight(object me);
int do_mo(string arg);
int do_toukan(string arg);
void create()
{
	set("short", "�ؾ����¥");
	set("long", @LONG
ǧ������������ִ��ԭ����֮ţ�����Դ�Ħ�������£������˲ı�������
���в��ٸ�ɮ�������棬�㼯�����ճ��������µ�������ʮ�����ա����־�
���������ڴˡ���¥���濪����ȷ��ͨ�硣�м����������Ŵ���ܡ��������
�а������Թ��Ķ�����λ��ɮ��ִ�������ڱ�Ŀ��˼��
LONG
	);

	set("exits", ([
		"down" : __DIR__"cjlou",
	]));
	set("cant_hubiao", 1);
    set("item_desc", ([
		
		"ͭ��" : (: look_tjing :),
	]));
     set("yjjbook",1);
	set("objects",([
		CLASS_D("shaolin") + "/hui-zhen" : 1,
		__DIR__"obj/wuji1" : 1,
		__DIR__"obj/wuji2" : 1,
		__DIR__"obj/wuji3" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if ((ob = present("huizhen zunzhe", this_object())) && living(ob))
		if (dir == "down" ) {
			foreach(ob in deep_inventory(me))
				if (ob->id("shaolin wuji"))
					return notify_fail("����˵�����书�ؼ�ֻ���ڲؾ�������ϰ������Я�������\n");
		}
	return ::valid_leave(me, dir);
}

void init()
{
	object me=this_player();
	add_action("do_jump", ({ "jump", "tiao" }));
	add_action("do_tui", ({ "tui", "push" }));
	add_action("do_dian", ({ "dian", "light" }));
		add_action("do_mo", "mo"); 
		add_action("do_mo", "find"); 
	add_action("do_toukan","toukan");
	if (me->query_temp("yjj/lookdown"))
	{
      call_out("yjj_fight",3,me);
	}
	if (!present("zhiqing",environment(me)))
	{ 
		new("/d/shaolin/npc/zhiqing.c")->move(environment(me));
		//new("/d/shaolin/npc/zhiyuan.c")->move(environment(me));
	}
} 

int do_jump(string arg)
{
	object me;
	me = this_player(); 
	//if (arg != "chuang" ) return 0;
	if ( !arg ) return 0;
	if (arg=="chuang")
	{		
	  if (!me->query_temp("marks/��"))
		return notify_fail("��Ҫ��ʲô��\n");

	  if (me->is_busy() || me->is_fighting()) 
		return notify_fail("����æ���ء�\n");
	  if( (int)me->query_skill("dodge",1) < 100 )
	   {
		message_vision(HIR"$N�ƿ�����������Ծ��ֱ�����⣬�����Ṧ������ˤ��������\n"NOR, me);
		me->unconcious();
		return 1;     
	    }
	   message_vision("$N�ƿ�����������Ծ��������һգ�۾Ͳ����� ��\n", me);
	   me->move(__DIR__"xiaojin1");
	   tell_room(environment(me), me->name() + "�Ӳؾ������Ծ�˹�����\n", ({ me }));
	   me->delete_temp("marks/��");
	   return 1;
	}
   
    if (me->query_temp("yjj/consider")&& (arg =="up"||arg =="����"))
     {
	   	   message_vision(HIC"$N��������������һ����Ծ���������������֮�󣬶��������\n"NOR,me);
		   me->move("/d/shaolin/foxiang3.c");
		return 1;  
    } 
}

int do_tui(string arg)
{
	object me = this_player();

	if( !arg || arg !=  "chuang") return 0;

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	write("������Ľ��ؾ���Ĵ����ƿ���\n");
	me->set_temp("marks/��", 1);
	return 1;
}

string look_tjing()
{	
	object mj,me=this_player();
	if (!present("mian ju",me)||!present("mask",me))
	   return "��û�����ݣ���ô��ҡ��ڽ����������ڶ����壿";
	if (me->query_temp("yjj/rushi"))
	{
		me->set_temp("yjj/lookjing",1);
        return "���н��Լ�����Ӱ���˳�����ͭ���������ľ侭�ʣ�����ǰ���ż�յ�͵ƣ���Ƶĵƹ�֮�£����������\n";
	}
	return "����һ��ͭ�������������˻ҳ���\n";
	
}

int do_dian(string arg)
{
   object me=this_player();
   if (!present("fire",me))
       return notify_fail("����ʲô������\n");
   if (!arg||arg!="����")
	    return notify_fail("��Ҫ��ʲô��");
   if (me->query_temp("yjj/lookjing"))
   {
	   message_vision(CYN"��������ĵƻ�$N��ϡ����ͭ����д�ˣ���һ����Ϊ�������λ���Ӱ����¶����磬�������ǹۡ�����\n"NOR,me);
       me->delete_temp("yjj/lookjing");
	   me->set_temp("yjj/fire",1);
	   call_out("yjj_wait1",3,me);
   }
   return 1;
}

int yjj_wait1(object me)
{
   me=this_player();
   message_vision(HIY"\n\n$NһЦ���ף���Ҫ�ٲ�����Ȼ����ͷ����ʲô��������һײ����ʱ���ˣ���ֻ֪����һ��ʱ�䣬\n"
                       +"������һ���쳣��Ҫ�����顣Ȼ����ʲô�£�ȴģģ������׽����ס��\n"
					   +HIG"\n\n$N����Ƭ�̣������л�ͷ����ͭ������һ�ۣ��������Լ��ı�Ӱ���͵�ʡ�򣺡��Ҳ���֮ǰ���������Լ��ı�Ӱ\n"
					   +"������ʲô�ط���������������ļ������Լ���Ӱ�������Գ��񣬺�����Ժ��Ų����죬���������˽�����\n",me);
  me->delete_temp("yjj/fire");
  me->set_temp("yjj/consider",1);
  return 1;
}

//���µ�����ս��������

int yjj_fight(object me)
{
     
	 object xbei,xsh;
	 object xji;
	 me=this_player();
	 if (!present("xuan bei",environment(me)))
        {
		  xbei=new("/kungfu/class/shaolin/xuan-bei.c");
		  xbei->move(environment(me));
         }
	   else xbei=present("xuan bei",environment(me));
       if (!present("xuan sheng",environment(me)))
        {
		 xsh=new("/kungfu/class/shaolin/xuan-sheng.c");
		 xsh->move(environment(me));
        }
	    else xsh=present("xuan sheng",environment(me));
	   if (!present("xuan ji",environment(me)))
        {
		 xji=new("/kungfu/class/shaolin/xuan-ji.c");
		 xji->move(environment(me));
         }
	   else xji=present("xuan nan",environment(me));
	  xbei->kill_ob(me);	 
      xsh->kill_ob(me);
	  xji->kill_ob(me);	
	  me->delete_temp("yjj/lookdown");
	  me->set_temp("yjj/mostart",1);
      return 1;
}


int do_mo(string arg)
{
   int i,j,g;
   object yjjbook;
   object me=this_player();
   if (!me->query_temp("yjj/mostart"))
        return notify_fail("��û���ܵ��ؾ�¥����ʲô������");
   if (me->is_busy()||me->is_fighting())
     return notify_fail("������æµ,��������ʲô������");
   if (!arg||arg!="book")
     return notify_fail("�㵽������ʲô������");
    if (me->query("yjj/powerup"))
      return notify_fail("���Ѿ����׽���ڻ��ͨ�����������ʲô��");
    if (time()-me->query("yjj/time")<86400)
      return notify_fail("��̫�ڿ���Ү��");
    message_vision(HIC"\n\n$N����ͭ��֮ǰ���������ʳָ���ھ������׾��ʵ�һ�е�һ����һ������һ�ơ����������ڵڶ��еġ��Ρ��������һ�£�\n"
	                 +"\n$N���룺����ɮ��˵�����ǡ�һ�����ǡ������Ϲ����ĸ����硯�֣���֪������һ����$N���˻ᣬ��ָ�ڵ����еĵ�һ�����硯����һ�ƣ�\n"
					 +"$N���鷽���������������̣����ڵ����еġ��ǡ�����һ�ơ�$N��ָδ�뾵�棬ֻ�����������죬ͭ���ѻ�������\n"NOR,me);
	 message_vision(HIG"\n\n$N��Ȼ���־��Ӻ����Ȼ��һ��С���������������Ǹ�С������ȥ��\n"NOR,me);
	 message_vision(HIC"$N���˰���ȴʲôҲ��������$Nһ���㣬����ʮ��ʧ��,������ԥ�������Ƿ�ת����ȥ��\n"NOR,me);
	 i=25;
	 j=random(me->query("kar"));
	 if(me->query("m-card-vip")) i =  20;
     if(me->query("y-card-vip")) i =  18;
     if(me->query("buyvip"))     i =  15;
	 i=random(i);
	 
	 g=random(me->query("relife/gifts/total"));
	//��Դ���������>=15�㣬�Ҹ���>=45
	if (me->query("kar")<31
		&& j>26
		&& i<3
		&& g>=15
		&& random(me->query("con"))>=40)
	{
      
	   message_vision(HIC"\n\n$N��Ȼ������ͭ���ı���һ�ţ�����ϲ�������������ˣ������ִ�ͭ������ժ��һ��СС���������ڻ��\n"
	   +"������·���ߣ�����ʱ����˷�Ⱥɮ�󼯣�����ȥ·��$N����һ���������Ӳؾ����ǰ���б��˳�ȥ��\n"NOR,me);
	   message_vision(HIY"\n\n��ϲ�㣬���Ե�ɺϣ�����ǧ����࣬�����ڻ�������ֵ�һ��--���׽����\n"NOR,me);
	   
	   yjjbook=new("/d/shaolin/obj/book-yijinjing.c"); 
	   yjjbook->move(me);
      // CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "��Ե�ɺ�֮��,�õ�һ��" + HIW + "��Ƥ���" + NOR + "��\n"); 
	 
	   message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ���������׽���������У�\n"NOR, users());

	   log_file("quest/yijj",sprintf("%s(%s) ��Ե�ɺϵõ����ֵ�һ��---�����׽����Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("yjj/fail"),me->query("combat_exp"),g,me));
	   me->set("title",HBYEL+RED"�׽�񹦴���"NOR);
	   me->set("yjj/powerup","pass");
	   me->delete_temp("yjj/mostart");
	   return 1;
	}
	else
	{
		message_vision(HIY"$N��Ȼ��֪�׽�����ڣ������Ե���������ܵõ��׽�洫��\n"NOR,me);
		log_file("quest/yijj",sprintf("%8s%-10s�����׽ʧ�ܣ�����Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("yjj/fail"),me->query("combat_exp"),g,me));
		me->add("yjj/fail",1);
		me->set("yjj/time",time());
		me->delete_temp("yjj/mostart");
        return 1;
	}
	
	return 1;
} 


int do_toukan(string arg)
{
   int i,j,k;
   object me=this_player();
   if (!me->query_temp("quest/mr/canhe/askbo"))
        return notify_fail("��û���ܵ��ؾ�¥͵��ʲô������\n���±������Ǵ�����\n");
   if (me->is_busy()||me->is_fighting())
     return notify_fail("������æµ,��������ʲô������");
   if (!arg||arg!="ָ���ؼ�")
     return notify_fail("��Ҫ��ʲô������");
    if (me->query("quest/mr/canhe/sanjue/pass"))
      return notify_fail("���Ѿ����κ�����ָ�ڻ��ͨ�����������ʲô��");
    if (time()-me->query("quest/mr/canhe/sanjue/time")<86400)
      return notify_fail("��̫�ڿ���Ү��");
    
	message_vision(HIC"\n\n$N������������ڲؾ�¥��¥�����±��˷��֣�Ȼ��ʼ��ϸ���Ҿ�¥��ָ���书�ؼ���\n"
	                 +"\n$N���룺��ʦ��˵����͵��ָ���ؼ������Ȳ鿴�Ƿ��н��ָ���黨ָ������Ҷָ���ؼ�������\n"
					 +"������������ϸ���ң��ܿ����������ҵ��������ؼ������д�ϲ�����¾ͷ���������\n"NOR,me);
	i=20;

	if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  16;
    if(me->query("buyvip"))     i =  13;
	j=random(i);
	k=random(me->query("kar"));
	//��Դ���������>=15�㣬�Ҹ���>=45,����Ҫ��
	
	if (k>27
		&&j<3)
	{
      
	   message_vision(HIG"\n\n$N���������飬��Ȼ�����һ�������Ľ�ݲ����ἰ�������еļ��ɣ���ʱ����\n"
	   +"������ԭ���κ�ָ��Ȼ����ʩչ�����ָ���黨ָ�Ͷ���Ҷָ����ʽ����\n"NOR,me);
	   message_vision(HIY"\n\n��ϲ�㣬���Ե�ɺϣ�����ǧ����࣬�������޵òκ�ָ����ָ��������\n"NOR,me);
	   
	 
	   message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ������ֲؾ�¥����ָ����ö���\n"NOR, users());

	   log_file("quest/mrsanjue",sprintf("%s(%s) ��Ե�ɺϵõ��κ�ָ������ָ��������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,j,me->query("quest/mr/canhe/sanjue/fail"),me->query("combat_exp"),me));
	   me->set("quest/mr/canhe/sanjue/pass",1);
	   me->delete_temp("quest/mr/canhe");
	   me->start_busy(1);

	   return 1;
	}
	else
	{
		message_vision(HIY"$N��Ȼ��֪����ָ��ʽ�������Ե���������ܵõ������ڻ��ͨ��\n"NOR,me);
		log_file("quest/sanjue",sprintf("%8s%-10s��������ָʧ�ܣ�����Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),k,j,me->query("quest/mr/canhe/sanjue/fail"),me->query("combat_exp"),me));
		me->add("quest/mr/canhe/sanjue/fail",1);
		me->set("quest/mr/canhe/sanjue/time",time());
		me->delete_temp("quest/mr/canhe");
        me->start_busy(1);
		return 1;
	}
	
} 
