// Npc: /d/tianshan/npc/npc.h
// By Linux
//modified by zhuifeng@SJFY

void attempt_apprentice(object ob)
{

		      
        if( (string)ob->query("gender") == "无性" ) {
                command ("say 对不起，灵鹫宫武技乃道家传承，讲究阴阳平衡，不收公公。");
                return;
        }
        if( !ob->query("quest/tonglao/pass"))  {
			command("你和本派无缘无故，凭什么可以进入灵鹫宫？\n");
            return;
        }
        command("say 咦，原来是你啊，童姥已经吩咐了，让你去找虚竹子先生，你可以拜他为师。");
        command("xixi "+ob->query("id"));
		//command("recruit " + ob->query("id"));
        
         return;
}

