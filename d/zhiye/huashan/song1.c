// Room: /d/huashan/song.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","ɽ����");
	set("long",@long
����һ���ɽ���Ա���Ȼ���ɵ�һ�����������Ȼɽ��������
�����������쳣�پ��������Զ��������ʯ���г�������������
�±ڣ�����һ�˲���֮����
long);
/*
	set("exits",([
	"enter" : __DIR__"hole2",
	"down" : __DIR__"v-road-5",
	]));*/
	set("cang",10);
    set("outdoors", "��ɽ");

	setup();
}
void init()
{
    object me=this_player();
	//if (me->query_temp("pxj/tiaochuang"))	  
	//{
		//call_out("pxj_jiasha",5+random(10),me);
	//}
	add_action("do_gou","gou");
	add_action("pxj_cang","cang");
	add_action("do_bang","bang");
	add_action("do_climb","pa");

}
int pxj_cang()
{
	object me=this_player();
	if (me->query_temp("hspxj/cang"))
	{
		return notify_fail("���Ѿ��غ��ˣ�\n");
	}
	if (me->query_skill("pixie-jian",1)<=150)
	{
		me->move("d/huashan/qinshi");
		message_vision(HIC"�������������������������Ⱥ������������"+me->query("name")+"����ˣ��ҿ������ˣ���������׽�Բ�ô��\n"NOR,me);
		message_vision(HIC"$Nڨڨ�Ĵ�����Ծ�ص������У������࣬�������Ρ�\n"NOR,me);
		return 1;
	}
	if (this_object()->query("cang")>0)
	{
		message_vision(HIY"\n\n$N��Ȼ�����˽Ų�����������⴫��������һ������æ������������á�\n"NOR,me);
		this_object()->add("cang",-1);
		me->set_temp("hspxj/cang",1);
		call_out("pxj_jiasha",5+random(5),me);
		return 1;
	}else {

		message_vision(HIR"$N������������󣬺�Ȼ���������Ѿ�����һ���ˣ���֮�£�����վ�����ȣ�һ�����е���ɽ�¡�\n"NOR,me);
		me->move("/d/huashan/v-road-1.c");
		me->set("qi",0);
		me->unconcious();
	
	if (me->query("kar")<10)
		me->die();
		me->set_temp("last_damage_from","��ɽ��ɽˤ�¶�");
		return 1;
	}

}

int pxj_jiasha(object me)
{
   message_vision(HIC"\n\n�����������غã����������ڴ����Ų�������Զ�������ƺ����������Ⱥ����˽�����\n"NOR,me);
   call_out("pxj_d1",3,me);
}

int pxj_d1(object me)
{
   message_vision(HIG"\n\n��ʦ�ã�ʦ�ã���Ȼᣬ�������Ҳ�С�ģ�ʦ��.....��$Nһ��֪����������Ⱥ���������������Ǻ��档\n"NOR,me);
   call_out("pxj_d2",5,me);
}

int pxj_d2(object me)
{
 message_vision(HIY"\n\nʦ�磬�Ҿ����������ɫ���ԣ��ǲ���������ϼ����Щ���鷳���ɱ�̫�󾫽����ǳ������������ƺ��������˵�������\n"NOR,me);
 call_out("pxj_d3",random(5),me);
}
int pxj_d3(object me)
{
 message_vision(HIG"\n\n\n����ȺЦ��һ����˵������û�а�������˳���úܡ�����\n"NOR,me);
 call_out("pxj_d4",random(5),me);
}
int pxj_d4(object me)
{
 message_vision(HIC"\n\n\n�����˵�����������ң�Ϊʲô�����˵����ɤ�ӱ��ˣ��ּ��ָߣ�����Ů���Ƶġ�����\n"NOR,me);
 call_out("pxj_d5",random(5),me);
}
int pxj_d5(object me)
{
 message_vision(HIG"\n\n\n����Ⱥ��������˵�˵�����˵���������������ġ���$N������˵��仰��ɤ���ͼ�úܣ�ȷ���Ǹ�Ů���ڴ�Ƣ����\n"NOR,me);
 call_out("pxj_d6",random(5),me);
}
int pxj_d6(object me)
{
 message_vision(HIC"\n\n\n������˵��������˵û�䣿��һ��֮�У��ʹ���û��������˵�������������޶��꣬��������ʲô�ⲻ�����£��������ң�����\n"NOR,me);
 call_out("pxj_d7",random(5),me);
}
int pxj_d7(object me)
{
 message_vision(HIG"\n\n\n����Ⱥ��������ʲô�ⲻ�����£�����ɽ֮�᲻Զ����������ͼ�̲����ɣ�������Ȼ���ҡ���Ϊ�˷��ģ���Ҳ���еġ�����\n"NOR,me);
 call_out("pxj_d8",random(5),me);
}
int pxj_d8(object me)
{
 message_vision(HIC"\n\n\n�����˵�������˵�˳�������ɱ𷢻���֪������ԩ���˳������\n"NOR,me);
 call_out("pxj_d9",random(5),me);
}
int pxj_d9(object me)
{
 message_vision(HIG"\n\n\n����Ⱥ���������������ħ�����˽�������ħ���Ǹ����εĹ������˽�飬���½�֪����ʲôԩ���ģ�����\n"NOR,me);
 call_out("pxj_d10",random(5),me);
}
int pxj_d10(object me)
{
 message_vision(HIC"\n\n\n������˵�������Ƕ��������м������Ҷ϶�������û�ñ�а���ס�������Ժ��֣��������ҵĽ�ѵ�������еġ�\n"
 +"������С�������䣬������͵͵�������¡��Դ�ɺ����ƽ��Ҫ�ã�����Ʋ��֮������Ȱ���֮�ˣ�"
 +"\n����ƽ��˫�ֽ����׷��͸�������Ҳ���Ʋ��ա�����\n"
 +"\n\n�������ּ���˵�������������Ź棬��ִ����ѵ�������Ż������˿��Է��顣����˵���ύ����������Ѿ����ˣ�\n"
 +"�α���ԩ����͵�����ף���ʵ����һ����׵öࡣ����֪��û��ƽ���ı�а���ס�������Ⱥȴ����������������ô֪��������ô֪��������\n"NOR,me);
 call_out("pxj_d11",random(5),me);
}
int pxj_d11(object me)
{
 message_vision(HIB"\n\n\n����Ⱥ������Ҳ�Ǽȸ�����������ŭ�У���ҹ֮�У���������ҹ�䣬$N���ɵ�ë���Ȼ��\n"NOR,me);
 call_out("pxj_d12",random(5),me);
}
int pxj_d12(object me)
{
 message_vision(HIC"\n\n\n����һ�ᣬ���������˻����ĵ���������Ȼ֪����ֻ��Ϊ�ⲿ���ף�����ȡ��ȥ�ġ���\n"
 +HIG"����Ⱥŭ����У����㡭����˵�������ҡ�������ֻ˵�˼����֣�ͻȻס�ڡ�\n"
 +"\n\n����������ʮ��ƽ����˵���������ճ�����˻��ԣ�������ֹѪ����֮ʱ�������������м����ģ�\n"
 +"д�����֣��ƺ��ǽ���֮�ࡣ�ڶ���������ҩ���Ǽ������Ѿ������ˣ���ʱ�����Ȼ����δ�ѡ�\n"
 +"���ʱ��֮�У��������Ҷ��ˣ����ޱ��˽�����������Ŀɲ������õġ�����\n"
 +HIC"\n\n\n������������ת��ͣ�˵������ʦ�磬�һ�ɽһ�ɵĽ��������ж��������裬��ϼ�񹦵��������ǲ�����\n"
 +"�Դ��������ۣ����������������ڽ�����ԭ������ȥ��ѧ���ɽ�����ֻ�ǽ���������Ұ�Ĵ�㣬ͼ�����ɡ���ɽ\n"
 +"һ���������У�˵ʲôҲ���������������С���������̩ɽ����ɽ����ɽ���ɣ���ʱ�����ɶ���һ�ɣ��ҿ�����\n"
 +"ռ������Ӯ�档������Ĳ�ʤ������������ҵľ綷һ����������������ɽ��Ҳ�����ˣ����˾�Ȫ֮�£�Ҳ����\n"
 +"���Ի�ɽ�ɵ��������ڡ���Ȱ�㻹���������������ѧ�˰ա�����\n"NOR,me);
 call_out("pxj_d13",random(5),me);
}
int pxj_d13(object me)
{
 message_vision(HIG"\n\n\n����Ⱥ��������������֪����ѧ��а�������㡭���㡭����͵�����𣿡������˵��������ֺα�͵����֪������\n"
 +"����Ⱥ������������˵����˵������˵����˻���ߣ��������죬ȴ�Ե���Ϊ���١���\n"
 +HIC"\n\n�����˵�������˵�������������Ѿ�ȫȻ���ˣ����˶����ó������ѵ����Լ����������ã�������Ⱥ����ǿ�磺\n"
 +"��������������ˡ��������˵�����ÿ���糿���㱻�����������������롭��������Ⱥȴ���һ���������Ƽ��ˣ�������\n"
 +"���Ǿ�����������̾�����������Ƽ��ˣ�һֱ��˵����ճ�ļ��룬���������ˣ�ȴ�����ù��������˼�ʮ����޵�����ˣ���\n"
 +HIG"\n\n\n����Ⱥ�����Ѱ�¶���޿��ٱ磬�������ã��ʵ��������˻���˭֪���ˣ��������˵�����û�С�������Ⱥ�ʣ���ɺ���أ���\n"
 +HIC"\n\n�����˵�����������֪���ġ�������Ⱥ������ƽ֮��Ȼ�Ҳ�֪�ˣ��������˵�������֪��������Ⱥ�������ã��������Ȱ��������ģ�\n"
 +"�������Ǿ��跨����ƽ֮���������뷨���������ˢ��ס���·�������ҽ��Ҳ�����ˡ���������ʮ�ֻ�ϲ��˵�������ǵ����ٺ�\n"
 +"Ҳû�С������⽣���������������ƽ�����������ǻ�ȥ�˵�Ϊ�ǡ�����\n"NOR,me);
 call_out("pxj_d14",random(5),me);
}
int pxj_d14(object me)
{
  message_vision(HIB"\n\n\n����Ⱥ��ʱ˵�������ܺã���������ȥ���ף���\n"
 +"$N���һ�������������ֹ���������ּ�֮����������к�������Ⱥ����Ȩ��ȥ����\n"
 +HIR"\n\n���ڴ�ʱ��ֻ���ô���ѽ��һ���򿪣�$N��æ��ͷ����ǰ���һ�����Ǽ�����Ʈ�����������Ŵ����ּ����ϡ�\n"NOR,me);
 me->delete_temp("pxj/tiaochuang");
 me->set_temp("pxj/yueover",1);
 return 1;
}
//��
int do_bang(string arg)
{
	object me=this_player();
	if (!arg || arg!="ǧ����")
	{
		return notify_fail("��Ҫ��ʲô��\n");
	}
	if (!present("sheng zi",me))
	{
		return notify_fail("��Ҫ��ʲô����\n");

	}
	message_vision(HIC"$N������һ�˰��������ϣ�һ��ϵ���Լ���������\n"NOR,me);
	me->set_temp("pxj/bang",1);
	return 1;
}

int do_gou(string arg)
{
	int i,j,s;
	object ob,me;
	me=this_player();
   // i=random(10);
	i=random(me->query("kar"));
	//ob=new("/d/fuzhou/obj/kuihua.c");
	if (time()-me->query("quest/pxj/super2/time")<86400)
	{
		return notify_fail("��̫�ڿ���Ү��\n");
	}

    if (me->query("quest/pxj/super2/pass"))
	{
		return notify_fail("���Ѿ��⿪�˱�а�����߼�ƪ,������ô�����ˣ�\n");
	}

	if (!arg||arg!="����")
	{
		return notify_fail("�������Ҫȥ��ʲô,�����Ӽ�ô��\n");

	}	

	if (!me->query_temp("pxj/yueover"))
	{
		return notify_fail("ɽ�������Σ�գ��������Ҫ��ʲô,�����Ӽ�ô��\n");
	}
  
	if (me->query("kar")>30)
	{
		log_file("quest/bugzuobi",sprintf("%s(%s)�ڽ��ܻ�ɽ�����±�а���߼�ƪ��֧�������������ɡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/pxj/super2/fail"),me->query("combat_exp"),me));
		return 1;
	}
    message_vision(HIY"\n\n\n$N�ۿ������Ĵ�����Ʈ���������ż�����һץ���������ߣ�û��ץ�������а�����ܷ�õ��Ϳ��Ƿ�ץ���������ˡ�\n"
    +"$Nȫ������������֮���⣬���ִ������ϵ�����֦�������������һ����\n"NOR,me);
   
   if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 50) 
   {
       message_vision(HIC"\n$N�����������ͱ�������ȥ����Ϊ���ϸ��ع��࣬ͻȻ$N����һ����ˤ��������\n"NOR, me);
		me->move("/d/huashan/v-road-1.c");
		me->set("qi",0);
		me->unconcious();
	
		if (me->query("kar")<10) {
			me->die();
			me->set_temp("last_damage_from","��ɽ��ɽˤ�¶�");
		}
		return 1;
	}

  
//�������Ӿ����������ٺ�
   if (!me->query_temp("pxj/bang"))
   {
	   message_vision(HIR"$Nһ��С�ģ�����̰�������������ʧ��ˤ��ɽ�£�������ȥ����������������������\n"NOR,me);
	   call_out("do_wait1",2,me);
       return 1;
    }
	
	

	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	s=random(j);
    
	if (me->query("kar")<31
		&& i>26
		&& random(me->query("int"))>35
		&& s<2)
	{
       message_vision(HIG"\n\n$Nֻ���ż��ƺ����������ģ����������������������˵ý������������Ĺ����ˣ�û����������Ԩ�С�\n"NOR,me);
	   message_vision(HIR"\n\n��ϲ�㣬��Ե�ɺ�֮�£��õ���а��������ƪ��\n"NOR,me);
	  
	   ob=unew("d/fuzhou/obj/kuihua");
	   if (ob)
	   {
		   
			message_vision("$N������ýŹ�ס���ģ�С����������뻳�С�\n", me);
			ob->set("reader", me->query("id"));
			ob->move(me);
		}
		else {
			message_vision("$NС�Ľ�����Ų�����ģ���Ȼ�����ı���һ����˲��Ʈ��ɽ�¡�\n", me);

		}
	   me->set("quest/pxj/super2/pass",1);	  
	  // ob->move(me);
	   me->set("title",HIM"Ⱥа����"NOR);
	   me->set("mytitle/quest/pxjtitle",HIM"Ⱥа����"NOR);
	   message("channel:rumor", HIM"��ҥ�ԡ�"+me->query("name")+"��Ե�ɺ�֮�£����һ���������ģ�\n"NOR, users());
	   log_file("quest/pxjf2", sprintf("%s(%s) �ɹ�����%d��Ŭ������Ե�ɺ��£��ɹ���ñ�а��������ƪ����ǰ����ֵi��%d,��ǰ���ֵs��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/pxj/super2/fail"),
		 i,
		 s,
         me->query("combat_exp")));	
	   
	   
	}
	else
	{
		message_vision(HIY"\n\n$N��ȻŬ�����һ�ţ���һ�����Ȼ�䴵������������Ĵ���������Ԩ��\n"NOR,me);
	    log_file("quest/pxjf2", sprintf("%s(%s) ��а��������ƪʧ��%d�Σ���ǰ����ֵi��%d,��ǰ���ֵs��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/pxj/super2/fail"),
		 i,
		 s,
         me->query("combat_exp")));
		
		me->add("quest/pxj/super2/fail",1);
		me->set("quest/pxj/super2/time",time());		
	    //destruct(ob);       
	} 
	me->move("/d/huashan/v-road-1.c");
	me->delete_temp("hspxj");
	me->delete_temp("pxj");
	message_vision(HIY"\n\n$N�������ӵ����ã�����������µ��µף����𷽲ŵľ��գ�������Щ���¡�\n"NOR,me);
	return 1; 
   
}

int do_wait1(object me)
{
   message_vision(HIY"ֻ��ɽ���Х���������岻���Լ����ƣ��������䣬���ŵĸε����ѣ�\n"
	                 +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +HIC"\n\n\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					   +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"NOR
					 +HIR"\n\n\n\n\         \        \       \        \              /\n"
					 +"\         \        \       \        \              /\n"
					 +"\         \        \       \        \              /\n"
					   +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"NOR,me);
     
	 me->set_temp("last_damage_from","����ɽ��ˤ");
	 me->die();	 
     return 1;

}
int do_climb(string arg)
{
	object me=this_player();

	if (!arg||arg!="up")
	{
		return notify_fail("��Ҫ���Ƕ�����\n");
	}
	if (!me->query_temp("pxj/bang"))
	{
		call_out("do_wait1",1,me);
		return 1;
	}
	if (arg=="up")
	{
		message_vision(HIY"$N���˽�ϵ����������ӣ�˫�ַ����������������ӵ���������������ɽ�¡�\n"NOR,me);
		me->move("d/huashan/qinshi");
		message_vision(HIC"����ɽ���Х��$N���𷽲ŵ��龰��������Щ���¡�\n"NOR,me);
		return 1;
	}

}