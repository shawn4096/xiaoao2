// app3.h
// ss 3 �� master

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say ����ͨ������ʦ�ܵĿ�����˵��\n");
		command("say ���кεº��ܰ���Ϊʦ��\n");
		command("say ���ֺ�ԭ�ι�����Ϊͽ��\n");
		command("say ����ɽ��Ҫ�ҳϵ���ͽ���㻹���������ҿ��ɣ�\n");
		return;
	}
	if (ob->query("family/family_name")!="��ɽ��")
	{
		command("say һ�����ǹ������֮ͽ��Ϊ�ε��ˣ�\n");
		return;
	}
	if(ob->query("party/gongji") < 2000 ){
		command("say ������ɹ�������2000���������ң�");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 200 ){
		command("say ��ĺ�������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 200 ){
		command("say ���������̫���ˣ�����300�������ң�");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say ���Ѿ�����ʦ��Ϊʦ�ˣ��ҿɲ������㣡");
		return;
	}
	if(ob->query("shen") > -500000 ){
		command("say ��ɽ�����Ժ������ƣ�<-500k������������ǻһ���Ͳ����ĺ������������");
		return;
	}
	command("say �ðɣ�ʦ����Ҫ�Ҷ�����һЩ������������ɽ���ء�");
	command("recruit " + ob->query("id"));
}