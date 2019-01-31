// Room: /d/shaolin/guangchang1.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

int init();
int do_open();
int xiao_ding1(object me);
int xiao_ding2(object me);
int xiao_ding3(object me);
int xiao_ding4(object me);
string look_gate();
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR5 "quest/�����˲�/��������ƪ/"

void create()
{
	set("short", "�㳡");
	set("long", @LONG
������������ǰ�Ĺ㳡�������㳡�ɴ�����ʯ�̳ɣ���Ϊƽ̹��������
����Զ������Щ���𡣴Դ�С�ݴ�ʯ��ķ�϶�г��˳������㳡��Χ��������
�������֣��Ľ��ϸ����˼���ʯ�����ּ�����Ϊģ������ǰ����ǽ���ߣ�����
���ݣ�����һ�����������������ߵ����ɼľ��ͭ����(gate)���Ϸ�һ���
�ң����ɷ�������š�[1;33m������[0;37;0m���������֡���ǰ����������վ�ż���ɮ�ˡ�
LONG
    );

	set("exits", ([
		"east" : __DIR__"gchange",
		"south" : __DIR__"shifang",
		"west" : __DIR__"gchangw",
	]));

	set("outdoors", "shaolin");
	set("item_desc",([
		"gate"        :    (: look_gate :),
	]));

	set("objects",([
		CLASS_D("shaolin") + "/qing-fa" : 1,
	]));

	setup();
	"/clone/board/shaolin_b"->foo();
}

int init()
{
  object me;
 
  me = this_player();
  if(!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"dagouzhen"))
  {
   tell_object(me,HIC"\n�������߳������£�����ɽ�ŵ�㳡��ͻȻ������һ�ֲ����Ԥ�С�\n"NOR); 
   message_vision(WHT"ɽ�´Ҵ�����һ���ˣ���$Nһ���ֵ������ٺ٣�ʩ������׺ݣ�������������Ǳ�޷𷨵úð�����\n"NOR,me);
   me->move("/d/gb/dagouzhen");
   tell_object(me,HIR"���ɻ���һ�£�ȴ��������Χ��һȦ�ˣ��ƺ���ؤ����󷨡�\n"NOR);
   log_file("quest/TLBB", sprintf("%s(%s)���ؽ����󡣾��飺%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return 1;
  }
	add_action("do_knock", "knock");
   //���������ս���������
   if (me->query_temp("xlz/askxiao1"))
   {
	   //me->delete_temp("xlz/askxiao1");
	   if (!present("ding chunqiu",environment(me)))
	   {
		   new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
		}
       if (!present("xuanci dashi",environment(me)))
	   {
		   new("/kungfu/class/shaolin/xuan-ci.c")->move("/d/shaolin/guangchang");
		}
	  if (!present("xingxiu dizi",environment(me)))
      {
	   new("/d/xingxiu/npc/xxdizi.c")->move("/d/shaolin/guangchang");
       }
	  //me->start_busy(3);
	  call_out("xiao_ding1",2,me);
	  //me->delete_temp("xlz/askxiao1");
	 // return 1;
   }

}

int close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");
	if(objectp(room)) {
	delete("exits/north");
	message("vision", "ƹ��һ�����������˰Ѵ��Ź����ˡ�\n", this_object());
	room->delete("exits/south");
	if (objectp(present("qingfa biqiu", room)))
		message("vision", "�巨������ǰ�Ѵ��Ź���������\n", room);
	else
		message("vision", "׳��ɮ����ǰ�Ѵ��Ź���������\n", room);
	}
	else message("vision", "ERROR: gate not found(close).\n", room);
}

int do_knock(string arg)
{
	object room;

	if (query("exits/north"))
		return notify_fail("�����Ѿ��ǿ����ˡ�\n");

	if (!arg || (arg != "gate" && arg != "north"))
		return notify_fail("��Ҫ��ʲô��\n");

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");

	if(objectp(room)) {
		set("exits/north", __DIR__"smdian");
		message_vision("$N������������ţ�ֻ��֨��һ����һλ׳��ɮ��Ӧ���򿪴��ţ�\n"
				"����������Ŀ���������´�����$N��\n",this_player());
		room->set("exits/south", __FILE__);
		message("vision", "���洫��һ����������׳��ɮ��Ӧ����ǰ�Ѵ��ſ���\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query_temp("xlz/askxiao1"))
	{
		notify_fail("�㻹�о���û���,�����뿪��\n");
		return;
	}
	
	if ( dir != "north" )
	return ::valid_leave(me, dir);

	if (is_wanted(me))
		return 0;
	if ( me->query("family/family_name") == "������" ) {
		if ( me->query("guilty") == 0
		 && me->query("K_record") == ( me->query("PKS") + me->query("MKS"))) {
			message_vision("׳��ɮ�˲����ÿ���˵����ʦ�������ˣ������\n", me);
			return 1;
		}
		else {
			if((int)me->query("guilty") == 0) {
				int shen = me->query("shen");
				if((int)me->query("shen_record") > shen)
					me->set("guilty", 1);
				else
					me->set("guilty", 2);
				me->set("K_record", me->query("PKS") + me->query("MKS"));
				if (shen > 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
				if (shen < 0 && -shen > me->query("combat_exp")) shen = -me->query("combat_exp");
				if (shen < 0) shen += shen / 9;
				else shen -= shen / 9;
				me->set("shen_record", shen);
			}
			write("׳��ɮ�˳���������˵��������Ժ�������Ŵ�ʦ��ʦ�ֻ���ȥ����Ժ�������й�����\n");
			return 1;
		}
	}
	else if( present("yingxiong ling", me)){
		message_vision("׳��ɮ�˺�ʮΪ�񣬲����ÿ���˵����ԭ���ǹ�ͼݵ�����������\n", me);
		return 1;
	}
	else if (me->query("luohan_winner")) {
		message_vision(HIY "׳��ɮ�˶�$N��ʮΪ�񣬲����ÿ���˵����ԭ���Ǵ����޺���Ĵ�Ӣ�ۼݵ�����������\n" NOR, me);
		return 1;
	}
	if (me->query("shen") >= 0) {
		if (me->query("gender") == "Ů��") {
			return notify_fail("׳��ɮ��˵������λŮʩ��������ذգ����´Ӳ��Ӵ�Ů�͡�\n");
		}
		else {
			return notify_fail("׳��ɮ��˵������λʩ����ذգ����²��Ӵ����ˡ�\n");
		}
	}
	return notify_fail("׳��ɮ����ʱ������ֿ��һ��ѩ���Ľ䵶���������λε�\n"
			"�����׼����ؿڣ���üŭĿ��˵�������аħ������������ҹ�����\n"
			"�Ժ��ٸ��߽�����һ��������ʱ��ն�����ǵĹ��ȣ�\n");

	if(me->query("no_quest"))
		return notify_fail("\n");
}

string look_gate()
{
	return "һ���������ߵ����ɼľ��ͭ���š�\n";
}


int xiao_ding1(object me)
{
 
   message_vision(CYN"\n���ĵ��Ա��ɴ����ƽ�һ�Ӱ����Ľ���ʮ���ƣ��Խ�ħ���̽�һ�Ӱ����Ĵ򹷰�������\n"
                      +"�����ɺ͹����������ã��⼸���书�������д���ĥ����֮������û�����ԵжԹ��У�\n"
					  +"���Ĳ��£�ȴ������ؤ���������������������������ˡ�\n"NOR,me);
   message_vision(HIB"\n��������������������̲�ס����һ������ͷ�������Եİ���һ�ۣ��������Ǹ��ӣ�\n" NOR,me);
   message_vision(HIG"\n�������񹦱�ؤ�ｵ��ʮ����ǿ�ö࣬��ô��ʹǿ�ģ���ʹ��ģ�\n"NOR,me);
   message_vision(HIG"\nׯʦ�֣����ϣ���ȻҪ�ö�ʦ�������ɴ�������񹦣�ȥ�����Ϻ��У�\n"NOR,me);  
   message_vision(HIG"\n���޵��ӷ׷�˵�����������񹦣����µ�һ��ս�޲�ʤ�����޲��ˡ��������ƣ���ƨ��ֵ����\n",me);
   message_vision(HIC"\n\n���޵��ӷ׷�˵�����������񹦣����µ�һ��ս�޲�ʤ�����޲��ˡ��������ƣ���ƨ��ֵ����\n",me);
   message_vision(HIB"\n\n���޵��ӷ׷�˵�����������񹦣����µ�һ��ս�޲�ʤ�����޲��ˡ��������ƣ���ƨ��ֵ����\n",me);
   message_vision(HIY"\n\n���޵��ӷ׷�˵�����������񹦣����µ�һ��ս�޲�ʤ�����޲��ˡ��������ƣ���ƨ��ֵ����\n",me);
   
   me->delete_temp("xlz/askxiao1");
   call_out("xiao_ding2",5,me);

   return 1;

}

int xiao_ding2(object me)
{
  
   message_vision(HIC"\n\n\nһƬ��������֮�У�������ɽ��һ����׳������˵������˭˵�������书ʤ����ؤ��Ľ���ʮ���ƣ���\n"NOR,me);
   call_out("xiao_ding3",5,me);
   return 1;

}
int xiao_ding3(object me)
{
  object ding,xf,xuan;
  //xuan=present("xuan ci",environment(me));
   
  if (!objectp(present("ding chunqiu",environment(me))))
  {
     new("/d/xingxiu/npc/ding.c")->move("/d/shaolin/guangchang");
  }
  ding=present("ding chunqiu",environment(me));

  // xx1=present("xingxiu dizi",environment(me));
   message_vision(HIY"\n������Ҳ���������������������Ĵ����˴��˶��У�����һ�֮�䣬��ס�˿ڡ�\n"NOR,me);
   message_vision(CYN"\n\n�������������ף�ʮ�����������ɽ�������ϳ˿�һɫ������ɫ��ձ��멣�������ɫ���£�\n"
                      +"�������ƻ������������˼Ƚýݣ������ۿ���ÿһƥ���Ǹ�ͷ���ȣ�ͨ���ë������������\n"
					  +"Ⱥ����ǰһ�������������ȴ��ÿƥ���������Ȼ�ǻƽ��͡�����һ����һʮ��������䲻���࣬\n"
					  +"����֮׳��ȴ������ǧ������һ�㣬ǰ��һʮ���ﱼ������������������һ�֣����һ����г۳���\n"
					  +"ؤ�����֮�У���Ⱥ���͵ظ������У����ǰ������ǰ����������������ڴ��˴��м�����������������ǰ����μ���\n"NOR,me);
  if (!present("xiao feng",environment(me)))
  {
	  xf=new("/d/nanyang/npc/xiaofeng.c");
      xf->move(this_object());
	 /* xf->delete("chat_msg_combat");
	  xf->set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: perform_action, "strike.sanzhang" :),
			  }));*/
	  message_vision(HIR"\n\n����첽���˹��������뵱����Ӣ��������Ȼ,���򶡴���ȵ��������ƣ�����\n"NOR,me);
  }
  ding->kill_ob(xf);
  ding->kill_ob(me);
  //����������

 
  call_out("xiao_ding4",30,me);
  //me->set_temp("xiaovsding",1);
  return 1; 
}

int xiao_ding4(object me)
{
    
	int i,j,g,t;
	object ding,xiao,xuanci,xxdizi;
	ding=present("ding chunqiu",environment(me));
	xiao=present("xiao feng",environment(me));
	xuanci=present("xuanci dashi",environment(me));
    xxdizi=present("xingxiu dizi",environment(me));
    if(file_name(environment(me))!="/d/shaolin/guangchang" ){
		message_vision(HIY"��Ϊ���Ѿ��뿪���ֹ㳡�����ڹ㳡������������һ����֪��\n"NOR,me);
        me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
        return 1;
	}
	/*if (!objectp(ding))
	{
		mesage_vision(HIC"����������ʹ����ʮ���ƵĿ����лھ���������֮�󽫶�������ڵء�\n"NOR,me);
	    mesage_vision(HIY"һȺ���ֵ������˳�������������Ѻ����ȥ��һʱ��㳡�ϱ���������塣\n"NOR,me);
		//destruct(dcq);
		//destruct();
     }*/
	message_vision(CYN"\n\n������Ŀ�����ǰ��һĻ���������Ѿ�������ȫ���Ľ���ʮ���ƣ��������д���������ʩչ������\n"NOR, me);
	message_vision(CYN"\ȴ��������ҽǣ��޼���Ѱ��ȴ����һ�����������������Ժ��м���ǧ���ɵĲ�����ӿ��\n"
			           +"��Щ��ʽ������˵���Ѿ���Ȼ���أ�һʱ֮�侹Ȼ��������..........................\n"
					   +"..............................................................................\n"NOR,me);

	j=random(me->query("kar"));
	g=random(me->query("relife/gifts/total"));
	//��Դ���������>=15�㣬�ұ���>45
	t=20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	i= random(t);
	
	if (me->query("kar")<31
		&& j>26
		&& i<3
		&& random(g)>=15
		&& random(me->query("str"))>40)
	{
       message_vision(HIC"$N��Ȼ�����⽵����Ҫ�����ɾ���һ��֮�������ڱ���Ҫ���Ǻܸߵġ�\n"NOR,me);
	   message_vision(HIC"$Nͬʱ�ڻ��ͨ����������Ҳ���似�ﵽ�۷�ı���֮·��ԭ������Ƿ�豹���ĵ���\n"NOR,me);
	   message_vision(HIC"$N��ϲ�㣬����ǧ�����գ��������������������������������ƾ�����\n"NOR,me);
	   xiao->command("chat* haha"+me->query("id"));
	   
	   xiao->command("chat "+"ؤ�ｵ��ʮ����������������Ե����Ʒ���");
	   xiao->command("chat* admire"+me->query("id"));
	   xiao->command("chat "+"����ʮ���ƣ����µ�һ�Ʒ�����ϲ��ϲ��");
	   if (objectp(ding)) destruct(ding);
	   if (objectp(xiao)) destruct(xiao);	
	   if (objectp(xuanci)) destruct(xuanci);
	   if (objectp(xxdizi)) destruct(xxdizi);
	   //me->add("combat_exp",15000);
	   log_file("quest/xlzsanzhang",sprintf("%s(%s) �����ֹ㳡���õ����������ָ�㣬���ܶ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
	    me->set("title",HIC"��Ժ����"+HIY"����ֿ��"NOR);
		me->set("mytitle/quest/xiaofengtitle",HIC"��Ժ����"+HIY"����ֿ��"NOR);
	   me->set("xlz/sanzhao","pass");
	   me->delete_temp("xlz/askxiao1");
	   me->start_busy(-1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N��Ȼ�����彵��ʮ���Ƶ��ռ����壬���������ʹ�õľ�������һʱ֮��ȴ��������⡣����ʮ���Ƶ�\n"
		+"������û�з��ӳ����������㻹���д������¸���������ѧϰ�ˡ��������û��������̾һ����������Ŭ��������һ��������׵ġ�\n"NOR,me);
		log_file("quest/xlzsanzhang",sprintf("%8s%-10s�����ֹ㳡�������л����в�û�гɹ�������Ŭ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��giftֵ��%d��\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/sanzhao/fail"),me->query("combat_exp"),g,me));
		me->add("xlz/sanzhao/fail",1);
		me->set("xlz/sanzhao/time",time());
		me->delete_temp("xlz/askxiao1");
		if (objectp(ding)) destruct(ding);
	    if (objectp(xiao)) destruct(xiao);	
	    if (objectp(xuanci)) destruct(xuanci);
	    if (objectp(xxdizi)) destruct(xxdizi);
		me->start_busy(-1);
        return 1;
	}
    
    
}