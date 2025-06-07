import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

print("asd")

df = pd.read_csv("results.csv")

type_map = {0: "random", 1: "reverse_sorted", 2: "nearly_sorted"}
df["data_type"] = df["type"].map(type_map)

plt.style.use('dark_background')
sns.set_theme(style="darkgrid", rc={
    "axes.facecolor": "#2E3440",
    "figure.facecolor": "#2E3440",
    "grid.color": "#4C566A",
    "text.color": "white",
    "axes.labelcolor": "white",
    "xtick.color": "white",
    "ytick.color": "white",
    "legend.facecolor": "#3B4252",
    "legend.edgecolor": "#4C566A"
})

palette = {
    "mergesort_lcp": "tab:blue",
    "quick3way": "tab:orange",
    "msd_radix": "tab:green",
    "msd_radix_switch": "tab:red"
}

for dt in df["data_type"].unique():
    sub = df[df["data_type"] == dt]
    plt.figure(figsize=(10, 6))
    sns.lineplot(
        data=sub,
        x="size", y="avgTimeMs",
        hue="algorithm", marker="o", palette=palette
    )
    plt.title(f"Time vs Size ({dt})", color="white", fontsize=14)
    plt.xlabel("Array Size", fontsize=12)
    plt.ylabel("Avg Time (ms)", fontsize=12)
    plt.legend(title="Algorithm", facecolor="#3B4252", edgecolor="#4C566A")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"time_{dt}_dark.png", facecolor=plt.gcf().get_facecolor(), dpi=300)
    plt.show()

for dt in df["data_type"].unique():
    sub = df[df["data_type"] == dt]
    plt.figure(figsize=(10, 6))
    sns.lineplot(
        data=sub,
        x="size", y="avgCharComps",
        hue="algorithm", marker="s", palette=palette
    )
    plt.title(f"Char Comparisons vs Size ({dt})", color="white", fontsize=14)
    plt.xlabel("Array Size", fontsize=12)
    plt.ylabel("Avg Char Comparisons", fontsize=12)
    plt.legend(title="Algorithm", facecolor="#3B4252", edgecolor="#4C566A")
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"comps_{dt}_dark.png", facecolor=plt.gcf().get_facecolor(), dpi=300)
    plt.show()
