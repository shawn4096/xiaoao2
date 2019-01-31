// Update by Lklv 2001.10.18

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_yangxiao();
string ask_yanxing();

void create()
{
	set_name("�º���", ({"guhong zi", "zi", "guhong"}));
	set("long","�����Ƕ����ɵ�������ʦ�ֹº��ӡ�\n"
		"����Ȼ�������ڣ�������һ�����ϣ�ֻ�ǲ��ϵ�����ʱʱ¶����������ɫ��\n"
	);
	set("gender", "����");
	set("attitude", "friendly");
	set("unique", 1);
	set("age", 55);
	set("shen", 20000);
	set("str", 32);
	set("int", 25);
	set("con", 30);
	set("dex", 28);
	set("max_qi", 15500);
	set("max_jingli", 6000);
	set("max_jing", 6500);
	set("neili", 18500);
	set("max_neili", 18500);
	set("jiali", 200);
	set("combat_exp", 9300000);

	set_skill("dacheng-fofa", 200);
    set_skill("linji-zhuang", 450);

	set_skill("jieshou-jiushi", 450);
	set_skill("huifeng-jian", 450);
	set_skill("sixiang-zhang", 450);
	set_skill("yanxing-daofa", 470);
	set_skill("hand", 450);
	set_skill("literate", 200);
	set_skill("strike", 450);
	set_skill("linji-jianzhen", 450);
	set_skill("sword", 450);
	set_skill("blade", 470);
	set_skill("parry", 450);
	set_skill("dodge", 450);
    set_skill("force", 450);
	set_skill("anying-fuxiang", 450);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("blade", "yanxing-daofa");
	map_skill("parry", "yanxing-daofa");
	map_skill("dodge", "anying-fuxiang");
	map_skill("strike", "sixiang-zhang");
	map_skill("hand", "jieshou-jiushi");

	prepare_skill("hand", "jieshou-jiushi");
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: perform_action, "blade.luandao" :),
			(: perform_action, "blade.chuanliu" :),
			(: perform_action, "blade.feiyan" :),
		(: perform_action, "hand.foguang" :)
	}));
	set("inquiry",([
		"����" : (: ask_yangxiao :),
		"���е�������" : (: ask_yanxing :),
		//"������" : (: ask_dragon :),
		//"�������" : (: ask_dragon :),
        ]) );
	create_family("������", 3, "���г���");
	setup();
	set_temp("apply/dodge", 40);
	set_temp("apply/attack", 40);
	set_temp("apply/armor", 40);
	carry_object(BINGQI_D("blade"))->wield();
	UPDATE_D->get_cloth(this_object());
}

void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	mapping myfam;
//	mapping lrn;
	int shen;
//	int lvl;
	myfam = (mapping)me->query("family");
	if (!myfam) return;
	shen = me->query("shen");
	if (shen < -200000 && myfam["master_name"] == "�º���"){
		command("say ���������������а�����ٲ�˼�ڸģ���Ҫ���㿪��ʦ�ţ�");
	}
/*
        if ( me->query("class") != "bonze" && myfam["family_name"] == "������"){
		lvl = (int)me->query_skill("linji-zhuang", 1);
		lrn = me->query_learned();
		if( !mapp(lrn) ) return;
		if( (int)lvl/10 == 14 && (int)me->query("emsujia")<1 ) {
			command("say �ټ�ׯ��Ҫ�и���ķ��ศ��������ͻ�ǰ��������");
			command("say �����׼ҵ������ײ�������������ŵ�������Ǳ�����");
			command("say ����ڹ���Ϊ��˵�ѵ���һ����Σ����������Ҫ����ɽ����һ�¡�");
			tell_object(me, "������ʦ���Ļ�,�������\n");
		}
		if( (int)lvl/10 == 16 && (int)me->query("emsujia")<2 ) {
			command("say �ټ�ׯ��Ҫ�и���ķ��ศ��������ͻ�ǰ��������");
			command("say �����׼ҵ������ײ�������������ŵ�������Ǳ�����");
			command("say ����ڹ���Ϊ��˵�ѵ���һ����Σ����������Ҫ����ɽ����һ�¡�");
			tell_object(me, "������ʦ���Ļ�,�������\n");
		}
		if( (int)lvl/10 == 17 && (int)me->query("emsujia")<3 ) {
			command("say ͽ������Ĺ����Ѿ�������Ϸ��ˡ�Ϊʦ��һ׮��Ը���Ǿ�����Ϊʦ������֮���ܹ��ٿ�һ��(show)���콣��");
		}
	}
*/
}

void attempt_apprentice(object ob)
{
        object me;
        mapping ob_fam, my_fam;
        string name;

	me = this_object();
	my_fam  = me->query("family");
	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������") {
		command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}
	if ((int)ob->query_skill("linji-zhuang",1) < 75) {
		command("say " + RANK_D->query_respect(ob) + "������ټ�ʮ��ׯ��Ϊ���������ܰ���Ϊʦ��");
		return;
	}
        if (!ob->query("luohan_winner") ) {
		command("say " + RANK_D->query_respect(ob) + "�������ѧ��Ϊ���������ܰ���Ϊʦ��");
		return;
        }
	if (ob->query("class") == "bonze" ) {
		command("say " + RANK_D->query_respect(ob) + "����ֻ���׼ҵ��ӡ�");
		return;
        }
	command("chat* haha");
	command("say �Ϸ���֮�꣬�յõ�һ���²����ˣ����ǿ�ϲ�ɺ� !");
	command("recruit " + ob->query("id"));
	return;
}

int accept_object(object who, object ob)
{
	mapping myfam = (mapping)who->query("family");
	if(myfam["family_name"] != "������"){
		command("say " + RANK_D->query_respect(who) + "�뱾��������������֪�˻��Ӻ�̸��");
		return 1;
	}
	//�õ����콣
	if (ob->id("yitian jian") && !this_object()->query("jian"))  {
		command("say �⡣������ǵ��걻ħ�̶��˶��ߵ����콣����");
		command("say �Ϸ�����֮�����ٿ�����ѽ���������Ҳ�Ŀ�ˡ�");
		command("say �����������ܹ�����������⡣");
		message_vision(HBGRN"�º��Ӷ�$N�̵���һ����$N�о���������һ��������\n"NOR,who);
		//who->set_temp("emei/jianjue",1);
        	who->add("shen",5000);
		call_out("dest", 1, ob);
        	set("jian",1);
		call_out("delete", 900, "jian");
        who->set_temp("yanxing/showyitian",1);
			return 1;
	}
	//�õ���ͷ
	if(ob->query("name") == "���е��׼�" && ob->query("id") == "shouji")
	{
		
		if (!who->query_temp("yanxing/askghz"))
		{
			command("say ��Ī�������ɱ�˸��ˣ����Һθɣ�\n");
			return 1;
		}
		if(ob->query("kill_by") != who){
			command("say ������������ɱ�İɣ�������ô�õ�����ͷ�ģ�");
			return 1;
		}
		
		command("say �ã�����ɱ������ΪΪʦ���𣬲������Ҵ�����׼Ҵ���ӣ�");
		command("thumb "+ (string)who->query("id"));
		who->set_temp("yanxing/killyang",1);
		call_out("dest", 1, ob);		
		
		who->add("shen", MAX(ABS(who->query("shen"))/5,50000) );//����shen ����exp����
		
		if(who->query("shen") > who->query("combat_exp"))
			who->set("shen", who->query("combat_exp"));//for hsdizi hehe
		who->add("combat_exp", 50+random(50));
		who->add("potential", 40);
		if(who->query("potential") > who->query("max_pot"))
			who->set("potential", who->query("max_pot"));
		tell_object(who,HIW"�㱻������һЩ����Ǳ�ܺ;���ֵ��\n"NOR);
		return 1;
	}
}

void dest(object ob)
{
	if (ob) destruct(ob);
}

string ask_yangxiao()
{
	object me,ob;
	me=this_player();
	ob=this_object();
	if (me->query("family/family_name")!="������")
	{
		return "�㲻���Ҵ���ҵĵ��ӣ��ѵ���ħ�̵ļ�϶����\n";
	}
	if (me->query("family/master_name")!="�º���")
	{
		return "�㲻���ҵĵ��ӣ�����Ҳ�ǰ��ʣ�\n";
	}
	
	message_vision(HIC"$N����$n��ǰ�������һЩ�������¡�\n"NOR,me,ob);
	command("say ���У���������������������������\n");
	message_vision(HIY"$n�������Ǽ�����$n�̲�סվ���������������������ǻ����ƺ�����ʲô�ش������һ�㣡\n"NOR,me,ob);
	command("say �������Ȼ����������£�Ϊʦ�͸���˵˵��Щ��֥���ҹ��ӣ�\n");
	command("say �������ʱ����������һλ���ָ��֣����˼�Ϊ���Ű��裡\n");
	command("say ָ��������ս����Ӣ����һʱ�䣬�����������Ĵ�˵�͹��£�\n");
	command("say Ϊʦ��ʦ����ɽ�������ʹ�����һ��С����������\n");
	command("say �������ϣ��Һ��������ˣ�\n");
	command("say ��ν���Ϊʦ�Ұ���������ʽ�£�\n");
	command("say ��ʱ��������ʢ��������������飬Ҳ�벻���������Ҿ���ʦ�ý������콣ȥ��������\n");
	command("say ˭֪�����ν�������Ȼ�Ǳ�����ܣ�\n");
	command("say ���������ҵ����콣������ȥ�����ֶ����ҵ���ǰ��\n");
	command("say Ϊʦ�ܴ���ܴ��裡\n");
	command("say ������ʹ��˼ʹ�������������������޵�����\n");
	message_vision(HIY"$N���ȵġ�������һ�������������Ƕ��ѵ�һ�����������\n"NOR,me);
	command("look "+me->query("id"));
	command("say �������ⷬ��ʶ��Ϊʦ������ο��\n");
	command("say �⵹������Ϊ�������ң���������ѧ���������ҷ������ж��ڽ����м�������裡\n");
	command("say Ϊʦ����ܾã�����ӽ�����������һ�����¶����Գ�Խ�������ѱ��˴��");
	command("say Ϊʦֻ������辶���������ó��������в���ѹ����������.....\n");
	command("say ���ŵ�������ӥצ�����ŵ�����֮��������Ϊʦ��Ե�ɺ�ϰ�ô����������ζ֮�·���Ψ�д����ܿ������е���ʽ.\n");
	command("say ��Ȼ������ŵ�������Ȥ����ȥ��������һ����ͷ��Ϊʦ�������Ҿ͸���˵���⵱�еľ��ϣ�\n");
	me->set_temp("yanxing/askghz",1);
	return "�����������У��Ҳ�ɱ���Ĳ�Ϊ�ˣ�\n";
}

string ask_yanxing()
{
	object me,ob;
	me=this_player();
	ob=this_object();
	if (me->query("family/family_name")!="������")
	{
		return "�㲻���Ҵ���ҵĵ��ӣ��ѵ���ħ�̵ļ�϶����\n";
	}
	if (me->query("family/master_name")!="�º���")
	{
		return "�㲻���ҵĵ��ӣ�����Ҳ�ǰ��ʣ�\n";
	}
	if (!me->query_temp("yanxing/killyang"))
	{
		return "��������ȥɱ������ô���㻹����ĥ��ʲô��\n";
	}
	if (!me->query_temp("yanxing/showyitian"))
	{
		return "���뿴�����콣����������Ҳ���ģ��㻹����ĥ��ʲô��\n";
	}
	if (me->query("quest/em/yxdf/jueji/pass"))
	{
		return "���Ѿ��⿪���գ���������ʲô��\n";
	}
	if (me->query_temp("yanxing/askzi"))
		return "����������У�\n";
	if (time()-me->query("quest/em/yxdf/jueji/time")<86400)
	{
		return "������̫�ڿ��ˣ�̰������ã�\n";
	}
	me->set_temp("yanxing/askzi",1);

	command("pat "+me->query("id"));
	command("say �ã��������������ģ���Ȼ����˷ܷ����ϣ�Ϊʦ�Ͱ����ž�ѧ�������㣡\n");
	message_vision(HIC"$N��������������������$n��ͷ,����$n�Ľ̻塣\n"NOR,me,ob);
	
	command("say ���ŵ�������ӥצ�����ŵ�����֮��������Ϊʦ��Ե�ɺ�ϰ�ô����������ζ֮�·���Ψ�д����ܿ������е���ʽ.\n");
	command("say ��Ȼ������ŵ�������Ȥ��Ҳ���Ϊʦ�����Σ��ҾͰ��⼸��������֪���㣡\n");
	command("say ���Ź����м�����ʽ���������⣡\n");
	command("say �������������Ҳ�û�з��֣�ֻ�������ŵ����ƺ����кܴ������û�з��ӳ�������һֱ��֪��Ϊʲô��\n");
	command("say ���ԴӺ�����һս��Ϊʦһֱ�ڿ�����δ�����У�\n");
	command("say ��׽��ÿһ��ʽ�Ĺ����У�Ϊʦ����֮�������ŵ������������������ԣ�\n");
	command("say ��Ҫԭ���Ǳ�����ʦ�������������ž�ΪŮ�ԣ���������������˵�Ƚϳ��أ����ʺ���ʹ��\n");
	command("say �ټ��ϱ����ķ����д�˷���Ϊ�����ԣ����Ӻ��⵶�����ء��͡��ס��ݵķ�����룡\n");
	command("say ���ԣ�Ҫ��ѱ��ŵ��������󣬱���Ҫ����־�ᶨ���Ա���Ҫ�ݣ����Լ���Ҫ�ݵ��׼����ӷ�����ϰ��\n");
	command("say ��Ҳ��Ϊʦ�ٳٲ����ҵ���Ҫԭ��Ψ��˷��ɽ�����Ҫ���������ӳ�����\n");
	command("say �㸽����������˵������.....\n");
	me->set_temp("yanxing/jueji",1);
	me->start_busy(999);
	call_out("yx_think",1,me);
	return "�����书ϰ�������ݺὭ��������ѧ�ı��ŵ������ڹ��ķ������澭���ؽ�����һ��¥��\n";
}
int yx_think(object me)
{
	int i,j;
	if(!me) return 1;
	me->set("quest/em/yxdf/jueji/time",time());
	if(me->query_temp("yanxing_thinking")<(10+random(3)))
	{
		me->add_temp("yanxing_thinking",1);
		if(random(2)) tell_object(me,HIG"\n��Ŭ���ػ���ղŹº�����ָ�����ÿһ�仰������,ֻ���ð�������...\n"NOR);
		else tell_object(me,HIY"\nͻȻ�䣬����ʽ��Ȼ��Щ�ֲڣ�����ȷ�����˷���ʤ����\n"NOR);
		tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��һ����ü��չ�����ӡ�\n"NOR, ({}));
		remove_call_out("yx_think");
		call_out("yx_think",3+random(3), me);
	}
	else
	{
		me->delete_temp("yanxing_thinking");
	
		i= 20;
		j=random(me->query("kar"));
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i= random(i);
	
		if (me->query("kar")<31
			&&j>=26
			&&i<4)
		{
			message_vision(HIC"\n\n$N���ڽ����е��������������ѧȫ���ڻ��ͨ����������\n"NOR,me);
			me->start_busy(1);

			message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+"��Ե�ɺϣ�ѧȫ���е��������������ﵽ����������ľ��磡\n"NOR, users());
			message("channel:chat", HIC"�����졿�º��ӣ�"+me->query("name")+"�����ҹº��������յ���һλ������ӣ������λ���������Ժ����ˡ���\n"NOR, users());

			log_file("quest/yanxingjueji",sprintf("%s(%s) �ӹº����Ķ��õ����е����ؾ��������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
				me->name(1), me->query("id"),j,i,me->query("quest/em/yxdf/jueji/fail"),me->query("combat_exp"),me));
			me->set("title",HIC"����"HIG"�º��Ӵ���"NOR);
			me->set("mytitle/quest/guhongzititle",HIC"����"HIG"�º��Ӵ���"NOR);
			
			me->set("quest/em/yxdf/jueji/pass",1);
			me->delete_temp("yanxing");
			return 1;
		}
		else
		{
			message_vision(HIY"\n\n$N��Ȼ���º���˵����������Щ���ϣ����������ʹ�õľ�������һʱ֮��ȴ���������\n"
			+"���е���������û�з��ӳ����������㻹���д������¸��º���ѧϰ�ˡ�\n"NOR,me);
			log_file("quest/yanxingjueji",sprintf("%s(%s) �ӹº���ѧϰ���е����ؾ�ʧ�ܡ������Դ��%d���������%d��ʧ�ܣ�%d������ֵ��%d��\n",
				me->name(1), me->query("id"),j,i,me->query("quest/em/yxdf/jueji/fail"),me->query("combat_exp"),me));
			me->start_busy(1);

			message("channel:chat", HIC"�����졿�º��ӳ�̾һ�����ƺ���"+me->query("name")+"����ʧ������\n"NOR, users());
			message("channel:chat", HIC"�����졿�º��������������һ�ղ�ɱ�����У�����һ����ʳ�Ѱ�������\n"NOR, users());

			me->add("quest/em/yxdf/jueji/fail",1);
			me->set("quest/em/yxdf/jueji/time",time());
			me->delete_temp("yanxing"); 	
			return 1;
		}  
	}
}