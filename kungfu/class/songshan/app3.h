// app3.h
// ss 3 代 master

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say 你先通过狄修师弟的考验再说！\n");
		command("say 你有何德何能拜我为师？\n");
		command("say 我又何原何故收你为徒？\n");
		command("say 大嵩山需要忠诚的门徒，你还是先做给我看吧？\n");
		return;
	}
	if (ob->query("family/family_name")!="嵩山派")
	{
		command("say 一看就是鬼鬼祟祟之徒，为何到此？\n");
		return;
	}
	if(ob->query("party/gongji") < 2000 ){
		command("say 你的门派功绩不够2000，别来找我！");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 200 ){
		command("say 你的寒冰真气太弱了，不足300别来找我！");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 200 ){
		command("say 你的嵩阳手太弱了，不足300别来找我！");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say 你已经拜我师兄为师了，我可不敢收你！");
		return;
	}
	if(ob->query("shen") > -500000 ){
		command("say 嵩山剑法以狠辣著称（<-500k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}