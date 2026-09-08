import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.animation import FuncAnimation, PillowWriter
from pathlib import Path


def main(name) -> None:
    def update_pos(time):
        x = values["estimated_missile_position_x"].iloc[:time + 1]
        y = values["estimated_missile_position_y"].iloc[:time + 1]
        line.set_data(x, y)
        point.set_data([x.iloc[-1]], [y.iloc[-1]])
        return line, point


    values = pd.read_csv(f"cmake-build-debug/Results/{name}.csv")

    xmin = values.true_missile_position_x.min()
    xmax = values.true_missile_position_x.max()
    ymin = values.true_missile_position_y.min()
    ymax = values.true_missile_position_y.max()

    fig, ax = plt.subplots()
    line, = ax.plot([], [], label="Missile trajectory")
    point, = ax.plot([], [], "ro")

    ax.set_xlim(xmin, xmax)
    ax.set_ylim(ymin, ymax)

    ax.set(xlabel="x", ylabel="y")
    ax.grid(True)
    ax.legend(loc="lower right")

    animation = FuncAnimation(
        fig,
        update_pos,
        frames=range(0, len(values), 5),
        interval=50,
        blit=True
    )


    plots_directory = Path("Plots")
    plots_directory.mkdir(parents=True, exist_ok=True)

    animation.save(
        f"Plots/{name}.gif",
        writer=PillowWriter(fps=20),
    )


if __name__ == "__main__":
    main('P003 R01-20260908T150929Z')