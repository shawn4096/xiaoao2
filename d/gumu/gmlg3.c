// Modify By River 98/08/29
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIR"������"NOR);
	set("long", @LONG
��������һ�ң�ȴ����һ�䴦���Գƣ����ִ����෴�����Ǻ�խǰ����Բ��
�ǣ��Ҷ�Ҳ�ǿ������������š��˴����ǹ�Ĺ����ʦ�ֳ�Ӣ���书֮�ء�
LONG
     );      

	setup();
}

void init()
{
	add_action("do_xiulian", "xiulian");
	add_action("do_yanxi", "yanxi");
	add_action("do_tui","tui");
	add_action("do_guanwu", "guanwu");
}

int do_yanxi(string arg)
{
	mapping fam;
	object me = this_player();
	
	if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
		return notify_fail("�㲻�ǹ�Ĺ���ˣ�����������Ĺ�书��\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");

	if ((int)me->query_skill("literate", 1) < 10)
		return notify_fail("�㶷�ֲ�ʶ,�����ɶ? \n");            

	if (arg == "top"){
		if (me->query("gender") != "Ů��")
			return notify_fail("��Ů���Ľ�������֮����ֻ�ʺ�Ů����ϰ��\n");
		if ((int)me->query_skill("sword", 1) < 10)
			return notify_fail("���������̫��޷���ϰ��Ů���Ľ���\n"); 
		if (me->query_skill("yunu-jianfa", 1) >= 1)
			return notify_fail("���Ѿ�ѧ����Ů���Ľ����Լ��ú����ɡ�\n");      
		message_vision("$N�����Ҷ���ͼ�ƣ����д�Ħ��Ů���Ľ��ľ���֮����\n", me);
		me->receive_damage("jing", 5);
		me->receive_damage("jingli",15);
		me->improve_skill("yunu-jianfa", 2);
		return 1;
	}
	return 0;
}

int do_xiulian(string arg)
{
	mapping fam;
	object me = this_player();

	if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
		return notify_fail("�㲻�ǹ�Ĺ���ˣ�����������Ĺ�书��\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");          

	if (me->query("jing") < 40)
		return notify_fail("�㾫�����ܼ���,ȥ����ЪϢ��. \n");

	if ((int)me->query_skill("literate", 1) < 10)
		return notify_fail("�㶷�ֲ�ʶ,�����ɶ? \n");

	if (arg == "backwall"){
		write("�����������խխ��ʯ�ڣ���һ���������������ֱ�һ�����顣\n");
		if (me->query_skill("strike", 1) < 51)
			return notify_fail("�㿴�˰���ֻ��Ī����ʲôҲû��ѧ�ᡣ\n");
		if (me->query_skill("strike", 1) > 100)
			return notify_fail("�������ۻ룬���������������ˡ�\n");          
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("strike", (int)(me->query_int()/2)+(int)(me->query_skill("strike")/4));
		return 1;
	}
	if (arg == "frontwall"){
		write("���ȭֱ������ǰ�ڣ�ʯ���Ľ�,��Ҳ���Լ����;�����������\n");
		if (me->query_skill("cuff", 1) < 51)
			return notify_fail("�㿴�˰���ֻ��Ī����ʲôҲû��ѧ�ᡣ\n");
		if (me->query_skill("cuff", 1) > 100)
			return notify_fail("��ȭ���Ѹ����ޱȣ�ȴ����������\n");
		me->receive_damage("jing",15 + random(20));
		me->improve_skill("cuff", (int)(me->query_int()/2)+(int)(me->query_skill("cuff",1)/ 4));
		return 1;
	}
	if (arg == "westwall"){
		write("��������ʯ��̤�Ž��������Ĵ�Ħ���Ͻ������衣\n");
		if (me->query_skill("sword", 1) < 51)
			return notify_fail("�㿴�˰���ֻ��Ī����ʲôҲû��ѧ�ᡣ\n");
		if (me->query_skill("sword", 1) > 100)
			return notify_fail("���ʯ��������������ȫȻ����,�����ٷ�����. \n");
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("sword", (int)(me->query_int()/2)+(int)(me->query_skill("sword", 1)/4) );
		return 1;
	}
	if (arg == "eastwall"){
		write("��������ָ,���Ŷ����������ʯ��,ϸ�Ĳ����������շ�����. \n");
		if (me->query_skill("throwing", 1) < 51)
			return notify_fail("�㿴�˰���ֻ��Ī����ʲôҲû��ѧ�ᡣ\n");
		if (me->query_skill("throwing", 1) > 100 )
			return notify_fail("�㰵���շ�����,�ٲ�������ڴ�. \n");
		me->receive_damage("jing", 15 + random(20));
		me->improve_skill("throwing", (int)(me->query_int()/2)+(int)(me->query_skill("throwing", 1)/4 ));
		return 1;
	}
	return 0;
}

int do_tui(string arg)
{          
	object me=this_player();
	
	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");
	if ( arg == "westwall"){  
		message_vision(YEL"$N���ֵ���Բ�Ļ������˼��£�һ���ʯ�����ƿ����ֳ�һ�ȶ��š�\n"NOR,me);
		set("exits/out", __DIR__"gmlg2");            
		remove_call_out("close");
		call_out("close", 5, this_object());    
		return 1;
	}
	return notify_fail("��Ҫ��ʲô��\n");
}

void close(object room)
{
	message("vision",HIY"��ʯ�����˻���ԭλ���ֵ�ס�˳��ڡ�\n"NOR, room);
	room->delete("exits/out");
}

int do_guanwu(string arg)
{
	mapping fam;
	object me = this_player();
	if (!arg) return notify_fail("��Ҫ����ʲô��\n");
	
	if (!(fam = me->query("family")) || fam["family_name"] != "��Ĺ��")
		return notify_fail("�㲻�ǹ�Ĺ���ˣ�����������Ĺ�书��\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");

	if ((int)me->query_skill("literate", 1) < 200)
		return notify_fail("���literate����200,�����Ϳ�������������ɶ? \n");            
	if (me->query_temp("quest/gumu/gwml"))
		return notify_fail("�����ڹ��������еİ��أ����ܷ��Ķ���? \n");  
	if (arg == "top"){
		if (me->query("gender") != "Ů��")
			return notify_fail("��Ů���Ľ�������֮����ֻ�ʺ�Ů����ϰ��\n");
		if ((int)me->query_skill("sword", 1) < 200)
			return notify_fail("���������̫�����200���޷���ϰ��Ů���Ľ���\n"); 
		if (time()-me->query("quest/gumu/ynjf/mulan/time")<86400)
			return notify_fail("������Ҳ̫�ڿ��ˡ�\n");      
		if (me->query("quest/gumu/ynjf/mulan/pass"))
			return notify_fail("���Ѿ�ѧ����Ů���Ľ���ľ��������ںϣ�ȥ��ս����ȥ�ɡ�\n");      
		message_vision("$N�����Ҷ��Ľ��ƣ����д�Ħ��Ů���Ľ��ľ���֮����\n", me);
		message_vision(HIC"$N��Ȼ����һ����ֵ���ʽ����Ů������ľ�������Ȼ�����ں�һ��ʹ�ã�\n"NOR, me);
		message_vision(HIY"$Ņ��ͷ������ϸ��Ħ���������еİ��һʱ�䲻������\n"NOR,me);
		me->set_temp("quest/gumu/gwml",1);
		//remove_call_out("guanwu_mulan");
		call_out("guanwu_mulan",1,me);
		return 1;
	}
	return 0;
}


int guanwu_mulan(object me)
{
	int i,j;
	
	if(me->query_temp("guanwu_ml")<(10+random(5)))
    { 
	  me->add_temp("guanwu_ml",1);
      if(random(2)) tell_object(me,HIG"\nһ��ľ�����䣬��������ν���Ů���أ��㲻��������˼��������⣬\n"NOR);
             else tell_object(me,HIY"\n�ȳ���Ů��Ȼ���ν�ľ�����䣿...��ͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  //remove_call_out("guanwu_ml");
	  call_out("guanwu_mulan",3+random(3), me);
	  return 0;
	}
   else
   {  
	  me->delete_temp("guanwu_ml");
      j = 15;
      if(me->query("m-card-vip")) j =  12;
      if(me->query("y-card-vip")) j =  10;
      if(me->query("buyvip"))     j =  8;
	 // if (me->query("gender")=="Ů��")
	    // j=j-2;
	 
	  i= random(j);

     if(i=4 
		&& random(me->query("kar"))>25)
	 {
		tell_object(me,HIM"\n�㰴�չ�Ĺ���ݶ���Ů������Ҫ��ָ�㣬�������˽⣬��Ů�����İ����ƺ���Щ����Ӧ�֡�\n"NOR);
        
		tell_object(me,HIY"\n������ǧ����࣬���ڵó���Ը������Ů����������ɱ������ͨ��\n"NOR);
       	
		
		me->set("quest/gumu/ynjf/mulan/pass",1);
		me->set("quest/gumu/ynjf/mulan/time",time());
		me->start_busy(1);
		me->delete_temp("quest/gumu/gwml");
		log_file("quest/ynjfmulan", sprintf("%8s(%8s) ʧ��%d�κ�������Ů��������ɱ�е��ںϾ�����һ�Ρ�iȡֵ��%d|���飺%d��\n", me->query("name"),me->query("id"), me->query("quest/gumu/ynjf/mulan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/ynjf/mulan/fail",1);
		
		tell_object(me,HIY"�����ǽ���ϵ���ʽ��������Ů�����ںϵİ��أ�ʼ��ȫȻ����Ҫ�졣\n\n"NOR);
		tell_object(me,HIG"\n������Ů��������ɱ���ں�ʧ�ܡ��ٽ�������\n\n"NOR);
		me->start_busy(1);
		me->add("quest/gumu/ynjf/mulan/fail",1);
		me->set("quest/gumu/ynjf/mulan/time",time());
		me->delete_temp("quest/gumu/gwml");
		log_file("quest/ynjfmulan", sprintf("%8s(%8s) ��Ů��������ɱ�н���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->query("name"),me->query("id"),me->query("quest/gumu/ynjf/mulan/fail"),i,me->query("combat_exp")) );
	  }
	return 1; 
  }

}
