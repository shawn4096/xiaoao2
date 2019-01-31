#include <ansi.h>
#include <job_mul.h>
//inherit F_MASTER;

inherit NPC;
int ask_job();
int ask_finish();
int ask_quit();
int ask_cure();
int ask_zhang();
int ask_zhou();
int ask_xie();
int ask_jinmao();
int ask_gmd();
int accept_object(object who, object ob);

object ppl;

void create()
{
	set_name("����", ({ "zhao min", "zhao", "min" }));
	set("gender", "Ů��");
	set("long", "�����ɹ��������ĳ�Ů�����������绨���������еļ�Ʒ��\n");
	set("age", 18);
	set("str", 20);
	set("int",35);
	set("con",20);
	set("dex",30);
	set("per",45);
	set("no_get", 1);
	set("combat_exp", 5000000);
	set("attitude", "friendly");
	set("max_qi",12000);
	set("max_jing",4000);
	set("neili",12000);
	set("max_neili",12000);
	set("qi",12000);
	set("jing",4000);
	set("jingli",4000);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("literate", 300);

	set("inquiry", ([
//                "����": (: ask_job :),
		"���": (: ask_finish :),
		"�˳�": (: ask_quit :),
		"��ҩ": (: ask_cure :),
		"������": (: ask_zhou :),
		"���޼�": (: ask_zhang :),
		"лѷ": (: ask_xie :),
		"��ë": (: ask_jinmao :),
		"Χ��������": (: ask_gmd :),
	]) );

	setup();
	carry_object(ARMOR_D("wcloth"))->wear();
	carry_object(ARMOR_D("pixue"))->wear();
}

void init()
{
	::init();
	add_action("do_quit", "abandon");
}

int ask_job()
{
	object me = this_player();
	int  exp;
	object where, target, *list;

	exp = me->query("combat_exp");
	if (me->query_temp("zhao")){
		command("say ��ȥ����ѽ��");
		return 1;
	}
	if (exp < 500000) {
		command("say ���书̫������\n");
		return 1;
	}
	if (me->query("potential") > me->query("max_pot")){
		command("say ����ȥ�������Ǳ�ܰɣ���˲����°빦����");
		command("giggle");
		return 1;
	}
	if( me->query_condition("job_busy")){
		command("say ��ʱ��û��ʲô����Ȥ���书��\n");
		return 1;
	}
	ppl = me;
	list = filter_array(users(), (:
    	    $1->query("combat_exp")/3 > ppl->query("combat_exp")/4
    	 && $1->query("combat_exp")/5 < ppl->query("combat_exp")/4
    	 && !wizardp($1)
    	 && $1->query_temp("user_type") != "worker"
    	 && query_idle($1)<120
    	 && !$1->query("menggu")
    	 && environment($1)
    	 && !$1->query_temp("caught")
    	 && !$1->query_temp("pigging_seat")
    	 && $1->query("duanzhi")<10
    	 && !$1->query_condition("ruanjin_poison")
    	 && $1->query("family")
    	 && query_ip_number($1) != query_ip_number(ppl)
   	 && !$1->query_condition("relax")
    	 && !$1->query_condition("wuguan_job")
	 && !$1->query_condition("killer")
    	:));
	list -= ({me,0});

	if(sizeof(list) < random(10)+1) {
		command("say ����ûʲô���֣����˰ɡ�\n");
		return 1;
	}

	target = list[random(sizeof(list))];
	if (target->query_temp("zm_job_time") > uptime()) {
		command("say ����ûʲô���֣����˰ɡ�\n");
		return 1;
	}
	target->set_temp("zm_job_time", uptime() + 3600);
	where = environment(target);
	me->set_temp("zhao/target",target->query("name"));
	me->set_temp("zhao/targetid",target->query("id"));
	me->apply_condition("job_busy", 4 + random(2));
	command("say ����ѧ��" + target->query("family/family_name") + "���书�������ȥץ����������");
	command("wink");
	command("whisper " + me->query("id") + " �뵽" HIR+ where->query("short") + CYN"��"HIW
	+ target->query("name") + HIY"(" + target->query("id") + ")"GRN"�����");
	command("say ���ʮ�����ɢ����ȥ�ɡ�");
	command("say �����޷�Ȱ��(quanxiang)����������(fu)�������");
	new(__DIR__"letter")->move(me);
	new(__DIR__"ruanjin")->move(me);
	message_vision(HIY"$N�õ���һС��ʮ�����ɢ��һ�����š�\n"NOR,me);
	return 1;
}

int ask_finish()
{
	object me, ob;
	int exp, pot;
	string ob_id;

	me = this_player();
	if (!me->query_temp("zhao")){
		command("?");
		return 1;
	}
	ob_id = me->query_temp("zhao/targetid");
	ob = present(ob_id, environment(me));
	if (!ob){
		command("say ���أ�");
		command("angry");
		return 1;
	}
	if (sizeof(filter_array(deep_inventory(ob), (:userp:)))) {
		command("hmm");
		command("whisper "+me->query("id")+ " ��һ���ô�����Ÿ��˰���");
		return 1;
	}
	if( !ob->query_condition("ruanjin_poison")
	 && (!ob->query_temp("convinced"))) {
		command("hmm");
		command("whisper "+me->query("id")+ " ����ôû����һ����һ��ѽ��");
		return 1;
	}
	command("hehe "+ob->query("id"));
	ob->apply_condition("wuguan_job",10+random(ob->query_kar()));
	message_vision("������������ʿ������$N�����ˡ�\n",ob);
	ob->move(__DIR__"jail");
	command("smile "+me->query("id"));
	command("say ����û��������ˣ�����ȥ��Ϣ�ɡ�");
	exp = random(4)+2;
	pot = me->query("combat_exp",1)/100000;
	pot += 100 + random(20) + me->query("job_time/����");
	if (me->query("menggu")) pot += 30 + random(10);
	
       	/*�������ƿ�ʼ*/
        if (me->query("registered")==3){
			exp = exp * ZM_JOB_MUL * VIP_MUL /10000;
            		pot = pot * ZM_JOB_MUL * VIP_MUL /10000;
		}
		else
		{
			exp = exp * ZM_JOB_MUL /100;
           		pot = pot * ZM_JOB_MUL /100;
		}
		/*�������ƽ���*/ 	
	
	
	me->add("combat_exp",exp);
	me->add("potential",pot);
	if (me->query("menggu")) me->add("balance", exp*10000);
	me->add("job_time/����",1);
	log_file("job/zhaomin", sprintf("%8s%-10s��%4d��ץ�˵õ�����%2d��Ǳ��%4d���־���%d��\n",
		me->name(1),"("+me->query("id")+")",(int)me->query("job_time/����"),exp,pot, me->query("combat_exp")), me);

	me->delete_temp("zhao");
	message_vision(HIW"$N�õ��� "HIM+exp+HIW" �㾭�飬"
		HIG+pot+HIW" ��Ǳ�ܣ�$N�ܹ���ץ�� "HIR+me->query("job_time/����")+HIW" ���ˡ�\n" NOR, me);
	GIFT_D->check_count(me,this_object(),"����");
	me->apply_condition("job_busy", 5 + random(3));
	return 1;
}

int do_quit()
{
	object me = this_player();
	object ob;

	if (ob = present("shixiang ruanjinsan", me)) {
		command("look " + me->query("id"));
		destruct(ob);
		command("kick3 " + me->query("id"));
		me->delete_temp("zhao");
		me->add_condition("job_busy", 6 + random(4));
		return 1;
	}
	return 0;
}

int ask_quit()
{
	object me = this_player();

	if (me->query("menggu")) {
		command("sneer");
		command("say ����Ҳ����Ҫ�����ַ����޳��ļһ");
		me->set("potential",0);
		me->add("combat_exp",-me->query("combat_exp")/100);
		message_vision(BLINK+HIR"$N��Ϊ�����޳������飬Ǳ�ܶ������ˡ�\n"NOR,me);
		me->delete("menggu");
		return 1;
	}
	return 0;
}

int accept_object(object who, object ob)
{
	//if(userp(ob)) return 0;
	
	if (!who->query_temp("lianji/askmin2")) {
		command("idle " +who->query("id"));
		command("say �����ʲô��ϵ������ ");
		return 0;
	}
	//��Ǯ
	if (ob->query("money_id") && ob->value() >= 500000) {
		if (!wizardp(who)) {
			command("en");
			return 1;
		}
		else {
			command("blush");
			command("remove all");
			command("lean "+who->query("id"));
			command("sweat "+who->query("id"));
			command("wear all ");
		}
		return 1;
	}
	//�������׼� ob->query("name") == "���������׼�" && && !who->query("zhou_shouji")
	if (ob->query("id")=="shouji"&& ob->query("name") == "���������׼�" )
	{
		if(ob->query("victim_user")) {
			command("say �ⲻ������������׼���");
			return 0;
		}
		if(ob->query("kill_by") != who){
			command("say ������������ɱ�İɣ�������ô�õ������ͷ�ģ�");
			return 0;
		}
		command("say �⾹Ȼ��"+ob->query("name"));

		command("say �ã�����ɱ��������Ϊлʨ�������Ҿͷ����ˣ�");
		command("thumb "+ (string)who->query("id"));
		who->set_temp("lianji/killzhou",1);
		destruct(ob);	
		//who->add("shen", -MAX(ABS(who->query("shen"))/5,50000) );//����shen ����exp����
		
		//if(who->query("shen") > who->query("combat_exp"))
		//	who->set("shen", who->query("combat_exp"));//for hsdizi hehe
		
		//who->add("combat_exp", 400+random(100));
		//who->add("potential", 40);
		
		who->set("zhou_shouji",1);//���ⷴ��ˢexp by renlai
		
		//if(who->query("potential") > who->query("max_pot"))
		//	who->set("potential", who->query("max_pot"));
		
		//tell_object(who,HIW"�㱻������һЩ����Ǳ�ܺ;���ֵ��\n"NOR);
		return 1;
	}
	
	return 0;
}

int ask_cure()
{
	object me = this_player();
	if (!me->query("menggu")) {
		command("en "+me->query("id"));
		return 1;
	}
//	else {
//		if (me->query("job_time/����")/25 > me->query("zhaocure")) {
			command("ok zhao min");
			new(__DIR__"cure")->move(me);
			me->add("zhaocure",1);
			message_vision(HIG"$N�õ���һ��ҩ�ۡ�\n",me);
			return 1;
//		}
/*		else {
			command("en");
			command("say ���ٰ�æ�Ҷ������°ɡ�");
			return 1;
		}
	}
*/
}

void kill_ob(object me)
{
	object ob;
	command("sneer " + me->query("id"));
	ob = present("lu zhangke",environment(me));
	if (ob) {
		ob->force_me("guard zhao min");
		ob->kill_ob(me);
	}
	ob = present("he biweng",environment(me));
	if (ob) {
		ob->force_me("guard zhao min");
		ob->kill_ob(me);
	}
	remove_all_enemy();
}

int ask_zhang()
{
	object me=this_player();
	if (!me->query_temp("lianji/askzhang"))
	{
		command("say ���޼����С�����žͲ��Ǻö������ѵ������Ķ���죿");
		command("say ��֪�����Ķ����������ӣ���Ȼ���Է��");
		return 1;
	}
	command("heng");
	command("say ����������ʲô��");
	command("say ��һ����ü���������ӣ��������������޼��Ƕ�����С��һ�����ӡ�");
	me->delete_temp("lianji/askzhang");
	me->set_temp("lianji/askmin1",1);
	return 1;

}
int ask_zhou()
{
	object me=this_player();
	if (!me->query_temp("lianji/askmin1"))
	{
		command("say ���������С椣�����������ģ�ʵ��һ���ݶ��ĳ���");
		return 1;
	}	

	command("heng");
	command("say ɱ�������յ�С椣��ҵ�ʤ��ʹ��˺ܶ࣡");
	me->delete_temp("lianji/askmin1");
	me->set_temp("lianji/askmin2",1);
	return 1;
}

int ask_xie()
{
	object me=this_player();
	if (!me->query_temp("lianji/askmin2"))
	{
		command("say ���ʵ����Ǹ�лѷ���Ҳ���ʶ����");
		//command("say �ߣ������������Ը����ˣ���������������Ż��\n");
		return 1;
	}
	if (!me->query_temp("lianji/killzhou"))
	{
		//command("say ���ʵ����Ǹ�лѷ���Ҳ���ʶ����");
		command("say �ߣ������������Ը����ˣ���������������Ż��\n");
		return 1;
	}
	command("heng");
	command("say ����Ƚ�˳�ۣ��Ҿ͸���������ɣ������ߵ��ϻ�����лѷ�Ǳ��������ݺ��ģ�");
	command("say ��Ҳ���Ǳ��������ݺ��ģ����򣬺ߺߣ�");
	command("say ��С椿��������޺���ʵ�����ն����ĺܣ�");
	command("angry ");
	command("say ���޼�������Ķ�����С��");
	me->delete_temp("lianji/askmin2");
	me->delete_temp("lianji/killzhou");
	me->set_temp("lianji/askmin3",1);
	return 1;

}

int ask_jinmao()
{
	object me=this_player();
	object jinmao;
	jinmao=new("d/mingjiao/obj/jinmao");
	if (!me->query_temp("lianji/askmin3"))
	{
		command("say ʲô��ë���Ҳ�֪����");
		return 1;
	}
	
	command("heng");
	command("say �ðɣ��������޼��Ǹ�С����������ģ�����͸���ɣ�");
	command("heng ");
	command("angry");
	jinmao->move(me);
	me->delete_temp("lianji/askmin3");
	
	me->set_temp("lianji/givejinmao",1);
	return 1;
}

int greet_zhang()
{
	command("hi zhang sanfeng");
	command("say ����ִ���������޼ɣ����յü������б���֮������Ҳ���磡��");
	command("xixi");
	command("say �δ��������������������Ī������λ��Ŀ�����ڱ������С�ÿ�������˵���ˣ�����ȴ���ް���");
	command("say �����˶��䵱��ѧ��Ҳ�����Ը��ý������˵�����ж����������ж��ա�");
	command("say ������һ��������Ȱ����֪�����˿ϸ�����");
	command("say ����֮�£�Ī������������֮����Ī�����������ɹŻʵ������ĺ�������������Ч˳������������⣬\n�䵱�ɴ����ٳ裬�δ����������������ǲ��ڻ��¡�");
	command("say ����Ͷ��������ʶʱ����Ϊ���ܡ��������Կ��š�������ɮ���£�����ͶЧ�����ҳ�͢������Ҳ������\n����������׷�������ͺ�֮����ѣ��������գ�");
	command("say �ұ����������Ӻ����ɷ����ն����ˣ����������");
	command("say �����ϴ����䵱���������ɣ���֪��������Ŀ����ԭ���䵱�ɰ��к�ħ�̹�����ȫ��ħ�̳����������书��˵��ֵһ�ӡ�");
	command("say ��������ȴ�������ȥ���ԣ�������ʲô���ʵѧ��");
	return 1;

}

int greet_ada()
{
	command("say ������������������Ϊ����һ����ΪС�����Ⲽ�ã�û�뵽������װ��ͯ���ڴ˵������Ҵ��¡�");
	command("say ���������û��Ϣ���ٰ���С��ͯ��������̫ʦ������̫ʦ���̣�Ҳ�����ߡ�");
	command("angry ");
	command("say ʲô�������ͽ������ϲ���������һ����թ������С�������������ȥ�������Ľ�����");
	command("say С���㶮��ʲô�����������Ҽ��е��ô˽����˿����ԭ�������콣����������ʲô��ϵ��");
	command("say �Ҹ�ôҪ����˵����������ʬ��Σ��ѵֵ�������ׯ�����У������ᱡ����֮�");
	command("say ȥ����С�������۰�ն������");
	
	return 1;

}


int do_answer(string arg)
{
	object me = this_player();
	if (me->query_temp("fangqiscore")) {
	if (arg=="yes")
	{
		me->set("was_job/wasscore",0);//���was����
		message_vision(HIY"$N���������˵�ͷ��˵��������Ȼ����ˣ���Ը���ĸ�����������\n"NOR,me);
	}
	else
	{
		message_vision(HIY"$N������ҡ��ҡͷ��˵��������Ȼ����ˣ����ǲ��ܸ��������ˣ���\n"NOR,me);
	}
	remove_action("do_answer","answer");
	me->delete_temp("fangqiscore");
	}
	return 1;
}



string ask_gmd() 
{
	
	object me = this_player(), ob = this_object();
	int max,i;
	int totalexp=0, maxexp, minexp;//��ֹexp���̫��
	object obj1;
	object *ob_list;
	object ob2;
	object fbroom;
	object *team;
	
	
	team = me->query_team();
	
	if (me->query("shen")>0) return "�������ĵ�̫�ã��Ҳ����İ�������񽻸��㡣";	
	if (me->query("combat_exp")<10000000) return "��������δ�гɣ��Ҳ����İ�������񽻸��㡣";

   if (me->query("was_job/wasscore"))
    {
	        command("say �ߣ����Ȼ���������̣��������Ҵ���,��������ϴ�ĸ���ڹ�����������ǰ�õ��Ľ�����");
	        message_vision("����Ҫ��������»���,�����Ը�������(answer yes ),��Ը�������(answer no)��\n",me);
			add_action("do_answer","answer");
			me->set_temp("fangqiscore",1);
			return "�ٺ�...";
	}


	
	//��������ģʽ
	if (team){		
		
		
		if (team[0] != me) {		
		return "ֻ�ж���������ܽ�����";
	    }
		if (sizeof(team) > 5 ){
		 return "��ȥ�ж������˶࣬�������ӡ�";
		}
		
		maxexp=minexp=team[0]->query("combat_exp");
		
		
		for (i=0;i<sizeof(team);i++){			
			
		totalexp = totalexp + team[i]->query("combat_exp");
		
		if(team[i]->query("combat_exp") > maxexp) {
			maxexp=team[i]->query("combat_exp");
			//maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp") < minexp)
			  minexp=team[i]->query("combat_exp");		
			
			
		if (!team[i]){
			return "��Ķ�����������⣬���ɢ�������齨��";
		}
		
         if (!present(team[i])){			
			return "�ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����";
		}
        
		 if (team[i]->query("was_job/wasscore")) return "��Ķ����������������������̽������¡�";
		  
         if ((int)team[i]->query("shen")>0) 
			return "��Ķ����������˾��ӣ��Ҳ����İ�������񽻸��㡣";		 
		
		 if (team[i]->query("combat_exp")<10000000) 
			 
		 return "��Ķ���������������δ�гɣ��Ҳ����İ�������񽻸��㡣";	
   
		if( team[i]->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		{			
			return "���������ڽ���֮�У����ǻ����ȴ����������������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="�´�����") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸������´����£����ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="Χ��������") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸�����Χ�������������ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="������Ħ��") //added by tangfeng ��quest��ͻ
		{			
			return "���Ƕ������˸�������Ħ�£����ǻ����ȵ����������˵�ɡ�";
		}
		
		if (team[i]->query("job_name")=="�����ɹ�����" )
		return "���Ƕ������˸������ɹ���������";
		
		if (team[i]->query_condition("job_busy"))
		{			
			return "���Ƕ������˸�����������Ҫ��Ϣ��";
		}
		
		if (team[i]->query_condition("was_busy"))
		{			
			return "���Ƕ������˸������´�����������Ҫ��Ϣ��";
		}
		if (team[i]->query_condition("gmd_busy"))
		{			
			return "���Ƕ������˸�����Χ��������������Ҫ��Ϣ��";
		}
		if (team[i]->query_condition("killer")) 
			return "��Ķ������б��ٸ�ͨ�����ˡ�";
		
		
		
		if (me == team[i]) continue;
/*
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
		return "�㻹�ǽ�"+team[i]->query("name")+"���������˰ɡ�;
		}*/

	}
      if (minexp>100000000)
		  {
			  if ((maxexp-minexp)>maxexp*0.1)  return "��ȥ����������ҿ���λ��Ա�������ƺ��޴�������";			
		  }
		  else
		  {
			  if((maxexp-minexp) > 5000000) return "��ȥ����������ҿ���λ��Ա�������ƺ��޴�������";
		  }

		
	}  //���
	
	//����
	
	
//	if (!wizardp(me))	
//              return "��ʱ�ر�,������������֪ͨ!";
 if (!wizardp(me))	{
	if (me->query_temp("gmd_job/asked") )
		return "�㲻���Ѿ��ӹ���������";
	
	if (me->query("job_name")=="�´�����")
		return "��������´��������񣬻���ЪЪ�ɡ�";
	
	if (me->query("job_name")=="������Ħ��") return "������꿹����Ħ�����񣬻���ЪЪ�ɡ�";
	
	if (me->query_condition("was_busy")) return "��������´��������񣬻���ЪЪ�ɡ�";
	
	if (me->query_condition("gmd_busy")) return "�������Χ�����������񣬻���ЪЪ�ɡ�";
	
	if (me->apply_condition("gb_job_busy")) return "������꿹����Ħ�����񣬻���ЪЪ�ɡ�";
	
	if (me->query_condition("job_busy"))
		{			
			return "�������������Ҫ��Ϣ��";
		}
	
 }

	ob2 = new("/clone/npc/zhong-shentong");
	if( ob2 ){
		destruct(ob2);
	}	
	
			
	command("say �ҷ��֮��Ҫ�����ڶ෴�������������׵���壬���ܽ�������ʥ����������֮����Ȼ�����߽⡣\n" );	

	me->set_temp("gmd_job/asked",1);
	me->apply_condition("job_busy", 30);
	me->apply_condition("gmd_busy", 30);
	me->apply_condition("gmd_job", 12);		
	command("say �����ڸ������ƣ����Ǳ�����������������ɵ������һ��Χ����������\n");	
	
		
	if (team){
		
		me->set_temp("gmd_job/team",team);//��¼����		
		
	}

	return "�����в������֣�����ö�����֣��������ֵ���󣬲����󷨣���ȥΧ��(weigong)���Բ���ȫ���м��мǡ�";	
	
}


