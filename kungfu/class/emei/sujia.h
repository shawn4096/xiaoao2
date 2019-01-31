// emei sujia apprentice
// Lklv 2001.10.18 update

void attempt_apprentice(object ob)
{
	if ((string)ob->query("class") == "bonze" ){
		command ("say 我只收俗家弟子。");
		return;
	}
	if( (string)ob->query("gender") != "女性" ){
		command ("blush");
		command ("say 我只收俗家女弟子。");
		return;
	}
	command ("say 好吧！我就收下你做峨嵋派俗家弟子。");
	command("recruit " + ob->query("id"));
	if( (string)ob->query("class")!="bonze" ){
		ob->set("title", "峨嵋派俗家弟子");
//		ob->set("class","emsujia");
	}
	if (ob->query("shen")<80000)
	{
		command("say 我峨嵋乃堂堂正正的名门正派，你面带煞气，连80k的正神都不到，来此作甚？\n");
		return;
	}
}

int prevent_learn(object ob, string skill)
{
	if (skill == "dacheng-fofa") 
	{
		write("这门杂学只能通过读书自悟方能习得。\n");
		return 1;
	}
	return 0;
}
