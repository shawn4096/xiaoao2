// bashuxian.c (kunlun)

inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_zliangyi();
string ask_anjin();

#include <ansi.h>

void create()
{
	set_name("�����", ({ "ban shuxian", "ban" }));
	set("title", "���������ŷ���");
	set("long",
		"���������������š����ｭ��������������̫��ķ��ˡ�\n"
		"����һ����ĸߴ�İ���Ů�ӣ�ͷ�����ף�˫Ŀ������ü�ļ����ɷ����\n");
	set("gender", "Ů��");
	set("age", 44);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 26);
	set("int", 24);
	set("con", 28);
	set("dex", 28);

	set("max_qi", 23500);
	set("max_jing", 5000);
	set("neili", 23200);
	set("max_neili", 23200);
	set("jiali", 200);
	set("eff_jingli",5000);
	set("combat_exp", 9400000);
	set("score", 40000);
	set("liangyi", 1);

	set_skill("art", 150);

    set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("sword", 450);
	set_skill("leg", 450);
	set_skill("hand", 300);
	set_skill("throwing", 300);
	set_skill("sanyin-shou", 300);

	set_skill("liangyi-jue", 200);

	set_skill("xuantian-wuji",450);
	set_skill("taxue-wuhen", 450);
	set_skill("chuanyun-tui", 450);
    set_skill("liangyi-jian",450);	

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	map_skill("hand", "sanyin-shou");

	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");
	
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feipu" :),
		(: perform_action, "sword.jinzhen" :),
  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.duanyun" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
    create_family("������", 3, "���ŷ���");
	set("class", "taoist");
	set("inquiry",([
		"�ؼ�" : (: ask_me :),
		"�����Ǿ�" : (: ask_zliangyi:),
		"�����ְ���" : (: ask_anjin:),
	]));

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}
void attempt_apprentice(object ob)
{
	if(ob->query("gender")=="����"){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"������Щ�������Ҽ��˾ͷ���������߿���");
		return;
	}
	if(ob->query("appren_hezudao", 1) == 1) {
		command("say "+RANK_D->query_respect(ob)+"���ҿ������Ц��������ɱ���ˡ�");
		return;
	}  
	if(ob->query_skill("xuantian-wuji",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��������޼�������300,�ҿɲ������㡣");
		return;
	}
		if(ob->query_skill("chuanyun-tui",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��Ĵ�����̫��,����300�����ҿɲ������㡣");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"���̤ѩ�޺�̫��,����300�����ҿɲ������㡣");
		return;
	}

	command("say �ðɣ��Ժ���͸���ѧ�书�ɣ�����ð���ѧ�գ�����������");
	command("recruit " + ob->query("id"));
	ob->set("title","�����ɵ��Ĵ�����");
}
string ask_me()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	if( this_player()->query("gender") == "����")
		return "�����߿����ҿ���������Щ�����˾ͷ���";

	ob = unew("/d/kunlun/obj/lyj-book.c");

	if(!clonep(ob)) return "�������ˣ������澭�ѱ���ʦ�������ˡ�";

	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "�������ˣ������澭�ѱ���ʦ�������ˡ�";
	} 
	ob->move(this_player());
	return "��ʦ���������Ȿ�����ǽ��ĵá������û�ȥ�ú����С�";
}

string ask_zliangyi()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

	

	ob = unew("/d/kunlun/obj/liangyi-jue.c");
	//ob->move(this_object());
	if(!clonep(ob)) return "�������ˣ������澭�ѱ���ʦ�������ˡ�";
	
	if (this_object()->query("liangyi")<1&&clonep(ob) && ob->violate_unique())
	{
		destruct(ob);
		return "�������ˣ��������Ǿ��澭�ѱ���ʦ�������ˡ�";
	}else {
		//ob->move(this_player());

		ob->move(this_player());
		this_object()->add("liangyi",-1);
		return "��ʦ���������Ȿ�����Ǿ����ؼ������û�ȥ�ú����С�";
		
	}


}


string ask_anjin()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("sanyin-shou",1)<200)
	{
		return "��������ֵȼ�����200��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/sys/anjin/pass"))
	{
		return "��������֡������������Ѿ��⿪�ˣ�\n";
	}
	if (time()-me->query("quest/kl/sys/anjin/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ������ֽ���������·�ߣ����������ɵ�Ӳ������̫��ͬ��\n"
				   HIR"\n\n\n$N�������ֵľ�����ʾ��$n����\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n�����˵�ʦ��������ָ�㣬�����������Լ����������ֵ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n��������أ���Ȼ���Ѩһʹ��һ�ɾ����������֣����ʹָ������ޱȡ�\n"			    
						 +"���������������������ְ��������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/sys/anjin/pass",1);
		log_file("quest/klanjin", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������ְ�������,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/anjin/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ���������־��������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/klanjin", sprintf("%8s(%8s) ���������ְ�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/anjin/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����������ʿ��ָ�㣬���Ƕ������ְ��������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/sys/anjin/fail",1);
		me->set("quest/kl/sys/anjin/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź����������ְ�������ʧ��"+me->query("quest/kl/sys/anjin/fail")+"�Ρ�\n";
	}


}