
#include <ansi.h>
inherit NPC;

int do_look(string);
int ask_me();
string ask_skill();
string ask_sanwu();
void create()
{
	object ob;
	set_name("��Ī��", ({ "li mochou", "li", "mochou" }));
	set("long", "�����ü�Ϊ��ò���������Ŀ�����˲���������\n");
	set("nickname", HIR"��������"NOR);
	set("gender", "Ů��");
	set("rank_info/respect", "����");
	create_family("��Ĺ��", 3, "����");

	set("age", 27);
	set("attitude","heroism");
	set("str", 22);
	set("dex", 23);
	set("con", 20);
	set("int", 24);
	set("shen_type", -1);

	set_skill("parry", 150);
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("sword", 150);
	set_skill("throwing",100);
	set_skill("poison", 50);
	set_skill("meinu-quanfa", 150);
	set_skill("cuff", 150);
	set_skill("meinu-quanfa", 150);
	set_skill("yunu-shenfa", 150);
	set_skill("yunu-jianfa", 150);
	set_skill("yunu-xinjing", 150);
	map_skill("force", "yunu-xinjing");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	prepare_skill("cuff", "meinu-quanfa");
	set("jiali", 30);

	set("combat_exp", 1100000);

	set("max_qi", 3000);
	set("max_jing", 2200);
	set("eff_jingli", 2000);
	set("neili", 3500);
	set("max_neili", 3500);

	set("inquiry", ([
		"name" : "վԶ�㣡",
		"here" : "�Ҳ��Ǳ����ˣ���֪����",
		"��" : "����������������˼֮�ࡢ���֮�⣿",
		"½չԪ" : "�����Ǹ������С������ʲô��",
		"�����" : (: ask_me :),
		"����������" : (: ask_sanwu :),
		"�嶾����" : (: ask_skill :),
		"С��Ů" : "�����ҵ�ʦ�á����������ʲô��",
		"�ֳ�Ӣ" : "�����ҵ�ʦ�棬�������ʵ�����ʣ�С���������㡣",
	]));

	set("chat_chance", 2);
	set("chat_msg", ({
		"��Ī���������裬�������񣬸�����������䣬���Ǻ��ֱ������������\n",
		"��Ī�����������ϵر�˫�ɿͣ��ϳἸ�غ����\n",
		"��Ī�����������Ȥ�����࣬���и��гն�Ů����\n",
		"��Ī���������Ӧ�����������ƣ�ǧɽĺѩ��ֻӰ��˭ȥ����\n",
		"��Ī����Ɐ�У��������ǰ�Թ�������������·����į������ġ���������ƽ������\n",
		"��Ī���������л�Щ��ർ���ɽ��������ꡣ��\n",
		"��Ī���������Ҳ�ʣ�δ���ˣ�ݺ�����Ӿ��������\n",
		"��Ī�������ǧ����ţ�Ϊ����ɧ�ˣ����ʹ�����������𴦡���\n",
	}));
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/zhen"));
		if (!ob) ob = unew(BINGQI_D("changjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(BINGQI_D("bb_zhen"));
       	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
    	carry_object(BINGQI_D("bb_zhen"));
		carry_object("/d/wudang/obj/greenrobe")->wear();
	}
}

void init()
{
	::init();
	add_action("do_look","look");
	add_action("do_look","hug");
	add_action("do_look","mo");
	add_action("do_look","18mo");
	add_action("do_look","kiss");
	add_action("do_look","lean");
	add_action("do_look","interest");
	add_action("do_look","flirt");
	add_action("do_look","pretty");
	add_action("do_look","love");
}

int ask_me()
{
	object me;

	me = this_player();
	message_vision(HIR "��Ī����Цһ���������������ȥ��������\n"NOR, me);
	kill_ob(me);
	return 1;
}

string *wheres=({
"/d/emei/xiaowu",		"/d/wudang/xiaolu1",		"/d/xiangyang/zhuquemen",
"/d/xiangyang/hanshui1",	"/d/fuzhou/road1",		"/d/xueshan/xuelu2",
"/d/xueshan/houzidong",		"/d/suzhou/lingyansi",		"/d/suzhou/liuyuan",
"/d/jiaxing/tieqiang",		"/d/hz/longjing",		"/d/hz/huanglong",
"/d/hz/yuhuang",		"/d/hz/tianxiang",		"/d/miaojiang/jiedao4",
"/d/foshan/duchang",		"/d/huanghe/shulin5",		"/d/hz/changlang1",
"/d/hz/yuquan",			"/d/hz/longjing",		"/d/xingxiu/shamo3",
"/d/wudang/xuanyue",		"/d/emei/guanyinqiao",		"/d/emei/basipan3",
"/d/tiezhang/shanmen",		"/d/tiezhang/hclu",		"/d/xueshan/huilang4",
"/d/emei/caopeng",		"/d/mingjiao/bishui",		"/d/mingjiao/shanting",
"/d/fuzhou/haigang",		"/d/fuzhou/laozhai",		"/d/xingxiu/shamo2",
"/d/jiaxing/nanhu",		"/d/village/caidi",		"/d/shaolin/songshu2",
"/d/xiangyang/tanxi",		"/d/huashan/husun",		"/d/huashan/yunu",
"/d/mr/yanziwu/xiaojing2",	"/d/mr/mtl/liulin",		"/d/suzhou/shihu",
"/d/suzhou/xuanmiaoguan",	"/d/suzhou/zijinan",		"/d/hengshan/cuiping2",
"/d/hengshan/guolaoling",	"/d/shaolin/talin1",		"/d/wudang/houshan/husunchou",
"/d/shaolin/shanlu8",		"/d/xueshan/shanlu7",		"/d/foshan/road10",
"/d/foshan/xiaolu2",		"/d/emei/jiulaodong",		"/d/hengshan/beiyuemiao",
"/d/gb/xinglin2",		"/d/city/shangang",		"/d/fuzhou/zhongxin",
"/d/huanghe/huanghe4",		"/d/lanzhou/shamo",		"/d/emei/gudelin3",
"/d/cangzhou/dongjie1",		"/d/tanggu/center",		"/d/putian/xl6",
"/d/dali/wuliang/songlin6",	"/d/gumu/xuantie/linhai8",	"/d/gumu/jqg/zhulin5",
});

string ask_skill()
{
	object me = this_player();
	object ob,room;
	int p, y=0;

	if (!me->query("family")
	 ||  me->query("family/family_name") != "��Ĺ��"){
		command("sneer "+ me->query("id"));
		return "���嶾�������Ǵ��嶾�ش����ݻ���������Ȼʦ�������ҵ���Ĺ���ӣ�����ȴ�Ӳ�������Ϊ��";
	}
	if ( time()-me->query("quest/gumu/wdsz/time") < 86400){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me) + "������Ҳ̫�ڿ��ˡ�";
	}
	if ( me->query_skill("yunu-xinjing", 1) < 200 ){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me)+"����Ů�ľ�������200������ѧ��Ҳ���á�";
	}

	if( me->query_temp("limochou/ask") && !wizardp(me))
		return "�Ҳ����Ѿ���������ô��������ȥ�����һء��嶾�ش�����";

	if(me->query("quest/gumu/wdsz/pass") && !wizardp(me))
	{
		command("? " + me->query("id"));
		if (me->query("askwudu-shenzhang")) return "���Ѿ��õ����һ�λ����ˡ�";
		if (!me->query_skill("wudu-shenzhang")) 	
           {
			   command("say " + "̫���ˣ���Ȼ��������ô��Ҫ�ľ�ѧ������ٽ���һ�Ρ�");
			   me->set("askwudu-shenzhang",1);
			   me->improve_skill("wudu-shenzhang", 10+random(me->query_int()));
			   return "�����»���嶾���ơ�";
		    }
		return "�㲻���Ѿ�ѧ�����嶾����ô��";
	}

	y = sizeof( filter_array(children("/d/jiaxing/npc/lu"),(:clonep:)));
	
	if(y > 0)
		return "��ʱ��û�������Ȥ�����ȥ�ɡ�";

	p = random(sizeof(wheres));
	room= find_object(wheres[p]);
	if (!room) room=load_object(wheres[p]);
	
	if(!objectp(room)) return "��ʱ��û�������Ȥ�����Ȼ�ȥ�ɣ�!";
	ob= new("/d/jiaxing/npc/lu");
	ob->move(room);
	me->set_temp("limochou/ask", 1);
	command("say ��С����һ�����Ź֣��ҷ�������˵����"+room->query("outdoors")+room->query("short")+"һ�������ȥ�����ҵ�����\n");
	message_vision(CYN"��Ī��¶��һ����Թ��֮ɫ��\n"NOR,me);
	return "���Ǳ����嶾�ش�����½��˫��С���˸�͵���ˣ�������ܰ����һش��飬�Ҿʹ������嶾���ơ�";
}

int accept_object(object who, object ob,object me)
{
	me= this_object();

	if( ob->query("id") != "wudu mizhuan"){
		command("say ������ⶫ������");
		return 0;
	}
	if( ob->query("owner") != who->query("id")
	 || !who->query_temp("limochou/ask"))
	{
		command("haha");
		command("say �ߣ����С���ˣ���Ȼ���ҵ��ؼ�͵����,�������ڻ����ˡ�");
		command("say ��л"+RANK_D->query_respect(who) + "��æ��СŮ�Ӷ�л�ˡ�");
		who->delete_temp("limochou");
		call_out("dest", 1, ob);
		return 1;
	}
	command("say �ðɣ���������ڿ죬���������Ҿʹ������嶾���Ƶ��ķ��ɡ�");
	command("whisper "+ who->query("id")+ " �Ʒ������������ζ����Զ��ߡ�֩�롢��ܡ���򼡢Ы�Ӷ�Һ����˫�֣�������֮��");
	command("say �������ˣ��ܷ�ѧ��Ϳ���ı����ˡ�\n");
	command("say ��ѧ���ᣬ��������һ������������");
	
	remove_call_out("thinking_wudu");
	call_out("thinking_wudu",1,who);
	//who->set("quest/gumu/wdsz/pass", 1);
	who->delete_temp("limochou");
	call_out("dest", 1 ,ob);
	return 1;
}

void dest(object obj)
{
	if(! obj) return;
	destruct(obj);
}

int do_look(string target)
{
	object me;

	me = this_player();
	if ( target
	&& present(target, environment()) == this_object()
	&& living(this_object()) 
    &&!me->query_temp("lmc/throw"))
                if ((string)me->query("gender") == "����" && me->query("combat_exp") >=200000) {
 
					message_vision(HIR "��Ī���ŭ���ȵ��������������Щ����ĳ����ˣ�ȥ���ɣ�\n"
+"��Ī�����ɱ��$N��\n"NOR, me);
			if ( present("bingpo yinzhen", this_object()) && ! this_object()->is_busy())
				me->set_temp("lmc/throw", 1);
			command("throw yinzhen at " + me->query("id"));
			kill_ob(me);
		}
}

void kill_ob(object me)
{
	object li;
	command("haha");
	
        if ( present("bingpo yinzhen", this_object()) && ! this_object()->is_busy())
			me->set_temp("lmc/throw", 1);

			command("throw yinzhen at " + me->query("id"));
	//	li=new("kungfu/class/gumu/lmc");
		//li->move(environment(me));
	//	li->kill_ob(me);
	//	destruct(this_object());		
	   ::kill_ob(me);
	   return;
}

int thinking_wudu(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_wudu")<(10+random(5)))
  { 
	  me->add_temp("canwu_wudu",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ���Ī����չʾ���嶾���Ƶ�һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
			 me->add_condition("snake_poison",1);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_wudu");
	  call_out("thinking_wudu",3+random(3), me);
   } else
   {  
	  me->delete_temp("canwu_wudu");     
      
	  j = 18;
      if(me->query("m-card-vip")) j =  14;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	  
	  i= random(j); 
 
     if(i<6 && random(me->query("kar"))>25)
	 {
		tell_object(me,HIG"\n�㰴����Ī���ָ�㣬���嶾���Ƶ����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIY"�㰴����Ī�����ԣ����Ʒ�����һ�飬��ʼ֮ʱ������ɬ��\n+"+
							"�Աߵ���Ī�����һ����ָ�����㼸���ؼ�Ҫ�㣬������������������\n"+
							"���Ȼ��������һƬ�����ѵ�����ʱ��ʹ��������Ī��ȵ�������ס����\n"NOR);
		tell_object(me,HIR"\n�㼱æ�������񣬴��Ѩһ���ʹ��������ӿ������ֱ���͹�Ѩ��ȥ����\n"+
							"\n��ϲ����Ե�ʻᣬ��ѧ���������嶾���ƾ�����\n"NOR);
       	me->improve_skill("wudu-shenzhang", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/gumu/wdsz/pass", 1);
		me->set("title",HIG"��Ĺ��Ī���"NOR);
		me->start_busy(1);
		log_file("quest/wudushenzhang", sprintf("%8s(%8s) ʧ��%d�κ󣬳��������嶾���Ƶľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/gumu/wdsz/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/wdsz/fail",1);
		me->set("quest/gumu/wdsz/time",time());
		command("heng ");
		tell_object(me,HIY"��������Ī���ָ�㣬��Ȼ�������嶾���Ƶİ��أ����Ƕ��嶾���Ƶ���������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/wudushenzhang", sprintf("%8s(%8s) �嶾���ƽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/gumu/wdsz/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}


string ask_sanwu()
{
	object me = this_player();
	

	if (!me->query("family")
	 ||  me->query("family/family_name") != "��Ĺ��"){
		command("sneer "+ me->query("id"));
		return "�����������������ҹ�Ĺ��������С֮��Ҳ�ң�";
	}
	if ( time()-me->query("quest/gumu/sanwu/time") < 86400){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me) + "������Ҳ̫�ڿ��ˡ�";
	}
	if ( me->query_skill("yunu-xinjing", 1) < 350 ){
		command("sneer "+ me->query("id"));
		return RANK_D->query_respect(me)+"����Ů�ľ�������350������ѧ��Ҳ���á�";
	}

	if(me->query_skill("wudu-shenzhang",1)<1 && !wizardp(me))
		return "��ѧ���嶾���ƣ����������ֲ����ڻ��ͨ��";

	if(me->query("quest/gumu/sanwu/pass") && !wizardp(me))
	{
		command("? " + me->query("id"));
		me->set("mytitle/quest/lisanwu",HIG"��������"NOR);
		return "�㲻���Ѿ�ѧ����������������ô��";
	}
	remove_call_out("thinking_sanwu");
	call_out("thinking_sanwu",1,me);
	me->start_busy(99);
	message_vision(CYN"��Ī��ݺݵ�˵����������Ϊ�������������޿ײ��룬����������С�\n"NOR,me);
	return "ֻҪ���������У�û�м���������ģ��Ҵ��Ĺ����ĺ��ء���������������";
}

int thinking_sanwu(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_sanwu")<(10+random(5)))
  { 
	  me->add_temp("canwu_sanwu",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ���Ī����չʾ�����������ֵ�һ��һʽ...\n"NOR);
             else tell_object(me,HIY"\nͻȻ�䣬���ƺ�ץ����ʲô...\n"NOR);
			  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking_sanwu");
	  call_out("thinking_sanwu",3+random(3), me);
   } else
   {  
	  me->delete_temp("canwu_sanwu");     
      j = 20;
      if(me->query("m-card-vip")) j =  15;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	  
	  i= random(j); 
 
     if(i<5 && random(me->query("kar"))>26)
	 {
		tell_object(me,HIG"\n�㰴����Ī���ָ�㣬�����������ֵ����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIY"�㰴����Ī�����ԣ����޷�����һ�飬��ʼ֮ʱ������ɬ��\n+"+
							"�Աߵ���Ī�����һ����ָ�����㼸���ؼ�Ҫ�㣬������������������\n"+
							"���Ȼ�������еı������ʹָ������ޱȣ�\n"NOR);
		tell_object(me,HIR"\n��ϲ����Ե�ʻᣬ��ѧ�����������������־�����\n"NOR);
       	me->improve_skill("yinsuo-jinling", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/gumu/sanwu/pass", 1);
		me->set("mytitle/quest/lisanwu",HIG"��������"NOR);
		me->start_busy(1);
		log_file("quest/sanwu", sprintf("%8s(%8s) ʧ��%d�κ󣬳����������������ֵľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/gumu/sanwu/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/gumu/sanwu/fail",1);
		me->set("quest/gumu/sanwu/time",time());
		command("heng ");
		tell_object(me,HIY"��������Ī���ָ�㣬��Ȼ���������������ֵİ��أ����Ƕ����������ֵ���������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/sanwu", sprintf("%8s(%8s) ���������ֽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/gumu/sanwu/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}