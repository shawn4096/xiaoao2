// lingqing jushi.c (ѩɽ�ɺ�)
// By sohu
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_anjin();
string ask_jiuwen();

void create()
{
	set_name("�����ʿ", ({ "lingqing jushi", "lingqing" , "jushi"}));
	set("title", "�����ɳ���");
        set("nickname", HIC"ѩ������"NOR);
	set("long",
		"�����������ɳ��ϡ����ｭ�����������������ʿ,�������Ⱥ��������������¡�\n"
		"��Ȼ����Ѵ󣬵���Ȼ���ó�������ʱ����ò��Ϊ������\n");
	set("gender", "Ů��");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 33500);
	set("max_jing", 7000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 7000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("parry", 500);
	set_skill("brush", 500);
	set_skill("blade", 500);

	set_skill("liangyi-jue", 200);
	set_skill("qingliang-shan", 500);
	set_skill("hand", 500);
	set_skill("sanyin-shou", 500);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);
	set_skill("throwing", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("leg", "chuanyun-tui");
	map_skill("dodge", "taxue-wuhen");
	map_skill("hand", "sanyin-shou");
	map_skill("parry", "qingliang-shan");
	map_skill("brush", "qingliang-shan");
	map_skill("throwing", "sanyin-shou");
	map_skill("blade", "qingliang-shan");


	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");

	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
  		(: perform_action, "throwing.xuejian" :),
  		(: perform_action, "hand.sanyin" :),
		(: perform_action, "leg.chuanyun" :),
	//	(: perform_action, "hand.sanyin" :),
		//(: perform_action, "leg.chuanyun" :),

		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
    create_family("������", 2, "���г���");
	set("class", "taoist");

	set("inquiry", ([
		"��ѩ�Ľ�����" : (: ask_anjin :),
		"��������" : (: ask_jiuwen :),
		//"��ϰ֮" : (: ask_su :),
		//"׷ɱ" : (: ask_ding :),
	]));

	setup();
	carry_object(BINGQI_D("bqsm_ding"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();

}
//���ܶ���
string ask_jiuwen()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say ������ص��ӣ�����������");
		return "�ߣ�\n";

	}
	if (me->query("gender")!="Ů��")
	{
		command("say �㲢��Ů�ԣ�����������");
		return "�ߣ�\n";
	}
	if (me->query_skill("sanyin-shou",1)<350)
	{
		command("say �������ֲ���350�����͵������ָ�������ȣ�");
		return "�ߣ�\n";
	}
	if (me->query_skill("xuantian-wuji",1)<350)
	{
		command("say �������޼�����350�����͵������ָ�������ȣ�");
		return "�ߣ�\n";
	}
	if (me->query_temp("qls/askjiuwen"))
	{
		command("say ���Ѿ�����˵����Щ�������£�Ϊ�β��ҽ�ȥ��");
		return "�ߣ�\n";
	}
	if (me->query_skill("qingliang-shan",1)>1)
	{
		command("say ���Ѿ�ѧ���������Ⱦ�������������ʲô��");
		return "�ߣ�\n";
	}
	command("say ��������ԭ���Ǳ�����֧����۵ľ�����\n");
	command("say ������ʱ�����ȴ������������Ƽʻ���ϵ�һ�ƴ�ʦΪʦ��\n");
	command("say ���ž���Ҳ����ʧ����ʵ�˱����ش���ʧ��������Ҳ���¼����ź���\n");
	command("say �������ľ�������һ�˴���ȥ�����������������Ƿ�Ը��黹���ž�����\n");
	me->set_temp("qls/askjiuwen",1);
	return "����\n";
}
int accept_object(object who,object obj)
{
//�����ݲ�ͬ������ͬ

	if (who->query("quest/kl/qls/pass")
		&&obj->query("id")=="qingliang miji"
		&&obj->query("owner")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("name")+"�����һ������ҷǳ����ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵�������Т�ģ��Һܿ����㣡\n");
		command("say ����ʲô�뷨�͸���˵�ɣ�\n");
		destruct(obj);
		who->set("quest/kl/qls/baishi",1);
		return 1;
	}	

	return 0;
}

void attempt_apprentice(object ob)
{
	if(ob->query("gender")=="����"){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"������Щ�������Ҽ��˾ͷ���������߿���");
		return;
	}
	if(ob->query("appren_hezudao", 1) == 1) {
		command("say "+RANK_D->query_respect(ob)+"���ҿ������Ц�����Ѿ����˺������ʦΪʦ��������ɱ���ˡ�");
		return;
	}  
	if(ob->query_skill("xuantian-wuji",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��������޼�������350,�ҿɲ������㡣");
		return;
	}
		if(ob->query_skill("chuanyun-tui",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"��Ĵ�����̫��,����350�����ҿɲ������㡣");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"���̤ѩ�޺�̫��,����350�����ҿɲ������㡣");
		return;
	}
	if(ob->query_skill("sanyin-shou",1) < 350){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"���������̫��,����350�����ҿɲ������㡣");
		return;
	}
	if (!ob->query("quest/kl/qls/pass")||!ob->query("quest/kl/qls/baishi"))
	{
		command("say ������Ե�޹ʣ�Ϊ��Ҫ�����ң�\m");
		return;
	}

	command("say �ðɣ��Ժ���͸���ѧ�书�ɣ�����ð���ѧ�գ�����������");
	command("recruit " + ob->query("id"));
	ob->set("title",HIC"�����������ʿ����"NOR);
	return;
}


//��ѩ�Ľ�

string ask_anjin()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "�㾹Ȼ�������صմ����ӣ���\n";
	}
	if (me->query_skill("sanyin-shou",1)<250)
	{
		return "��������ֵȼ�����250��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/sys/xuejian/pass"))
	{
		return "��������֡���ѩ�Ľ����Ѿ��⿪�ˣ�\n";
	}
	if (time()-me->query("quest/kl/sys/xuejian/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ������ֽ���������·�ߣ����������ɵ�Ӳ������̫��ͬ��\n"
						"�⹦�������׼ҵ��似�������������ط��Ʊ����������Ȼ����˸���Ȥ���Ҿ���ʾ�������Լ��������ˡ�\n"+
				   HIR"\n\n\n$N����Ծ�𣬽������ַ�ѩ�Ľ��ľ�����ʾ��$n����\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<6
		&& me->query("kar")<31
		&& j >= 23 ) 
	{
		tell_object(me,HIY"\n�����˵������ʿ������ָ�㣬�����������Լ����������ֵ������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n��������أ���Ȼ���Ѩһʹ��һ�ɾ����������֣����ʹָ������ޱȡ�\n"			    
						 +"���������������������ַ�ѩ�Ľ������÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/sys/xuejian/pass",1);
		log_file("quest/klxuejian", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������ַ�ѩ�Ľ�����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/xuejian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ���������ַ�ѩ�Ľ����������ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/klxuejian", sprintf("%8s(%8s) ���������ַ�ѩ�Ľ�����ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/xuejian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����������ʿ��ָ�㣬���Ƕ������ַ�ѩ�Ľ������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/sys/xuejian/fail",1);
		me->set("quest/kl/sys/xuejian/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź����������ַ�ѩ�Ľ�����ʧ��"+me->query("quest/kl/sys/xuejian/fail")+"�Ρ�\n";
	}


}