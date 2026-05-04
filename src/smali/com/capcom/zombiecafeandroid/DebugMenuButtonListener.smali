.class public final Lcom/capcom/zombiecafeandroid/DebugMenuButtonListener;
.super Ljava/lang/Object;
.implements Landroid/view/View$OnClickListener;


# direct methods
.method public constructor <init>()V
    .locals 0

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/view/View;)V
    .locals 5

    invoke-virtual {p1}, Landroid/view/View;->getContext()Landroid/content/Context;

    move-result-object v0

    new-instance v1, Landroid/app/AlertDialog$Builder;

    invoke-direct {v1, v0}, Landroid/app/AlertDialog$Builder;-><init>(Landroid/content/Context;)V

    const-string v2, "Mod Menu"

    invoke-virtual {v1, v2}, Landroid/app/AlertDialog$Builder;->setTitle(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;

    const/4 v2, 0x7

    new-array v2, v2, [Ljava/lang/CharSequence;

    const/4 v3, 0x0

    const-string v4, "+1 toxin"

    aput-object v4, v2, v3

    const/4 v3, 0x1

    const-string v4, "Max toxin"

    aput-object v4, v2, v3

    const/4 v3, 0x2

    const-string v4, "+1 money"

    aput-object v4, v2, v3

    const/4 v3, 0x3

    const-string v4, "+10k money"

    aput-object v4, v2, v3

    const/4 v3, 0x4

    const-string v4, "Max money"

    aput-object v4, v2, v3

    const/4 v3, 0x5

    const-string v4, "+10k XP"

    aput-object v4, v2, v3

    const/4 v3, 0x6

    const-string v4, "Max XP"

    aput-object v4, v2, v3

    new-instance v3, Lcom/capcom/zombiecafeandroid/DebugMenuItemClickListener;

    invoke-direct {v3}, Lcom/capcom/zombiecafeandroid/DebugMenuItemClickListener;-><init>()V

    invoke-virtual {v1, v2, v3}, Landroid/app/AlertDialog$Builder;->setItems([Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;

    const-string v2, "Close"

    const/4 v3, 0x0

    invoke-virtual {v1, v2, v3}, Landroid/app/AlertDialog$Builder;->setNegativeButton(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;

    invoke-virtual {v1}, Landroid/app/AlertDialog$Builder;->show()Landroid/app/AlertDialog;

    return-void
.end method
