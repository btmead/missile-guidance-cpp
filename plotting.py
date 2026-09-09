import sys
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.animation import FuncAnimation, PillowWriter
from pathlib import Path


def load_results(name):
    return pd.read_csv(f"Results/{name}.csv")


def minmax (values):
    minmax = {}
    minmax["x1min"] = values.estimated_missile_position_x.min()
    minmax["x1max"] = values.estimated_missile_position_x.max()
    minmax["y1min"] = values.estimated_missile_position_y.min()
    minmax["y1max"] = values.estimated_missile_position_y.max()
    minmax["x2min"] = values.estimate_missile_acceleration_x.min()
    minmax["x2max"] = values.estimate_missile_acceleration_x.max()
    minmax["y2min"] = values.estimate_missile_acceleration_y.min()
    minmax["y2max"] = values.estimate_missile_acceleration_y.max()

    return minmax

def create_plot(values):
    min_max = minmax(values)

    fig, (ax1, ax2) = plt.subplots(1, 2)
    missile_line, = ax1.plot([], [], "red", label="Missile trajectory")
    missile_point, = ax1.plot([], [], "ro")
    target_line, = ax1.plot([], [], "blue", label="Target trajectory")
    target_point, = ax1.plot([], [], "bo")
    missile_acceleration = ax2.plot([], [], "red", label="Missile acceleration")
    target_acceleration = ax2.plot([], [], "blue", label="Target acceleration")

    ax1.set_xlim(min_max["x1min"], min_max["x1max"])
    ax1.set_ylim(min_max["y1min"], min_max["y1max"])
    ax1.set(xlabel="x", ylabel="y")
    ax1.grid(True, alpha=0.3)
    ax1.set_aspect("equal", adjustable="box")
    ax1.legend(loc="lower right")
    
    ax2.set_xlim(min_max["x2min"], min_max["x2max"])
    ax2.set_ylim(min_max["y2min"], min_max["y2max"])
    ax2.set(xlabel="Time (s)", ylabel="Acceleration (m/s^2)")
    ax2.grid(True, alpha=0.3)
    ax2.legend(loc="upper right")

    return fig, missile_line, missile_point, target_line, target_point


def create_position_updater(
        values,
        missile_line,
        missile_point,
        target_line,
        target_point):
    def update_positions(time):
        xm = values["estimated_missile_position_x"].iloc[:time + 1]
        ym = values["estimated_missile_position_y"].iloc[:time + 1]
        xt = values["true_target_position_x"].iloc[:time + 1]
        yt = values["true_target_position_y"].iloc[:time + 1]
        am = values["estimated_missile_acceleration_y"].iloc[:time + 1]
        missile_line.set_data(xm, ym)
        missile_point.set_data([xm.iloc[-1]], [ym.iloc[-1]])
        target_line.set_data(xt, yt)
        target_point.set_data([xt.iloc[-1]], [yt.iloc[-1]])
        return (missile_line, missile_point, target_line, target_point)

    return update_positions


def save_animation(animation, name):
    plots_directory = Path("Plots")
    plots_directory.mkdir(parents=True, exist_ok=True)

    animation.save(
        f"Plots/{name}.gif",
        writer=PillowWriter(fps=30),
    )


def main(name) -> int:
    values = load_results(name)
    fig, missile_line, missile_point, target_line, target_point = create_plot(values)
    update_positions = create_position_updater(
        values,
        missile_line,
        missile_point,
        target_line,
        target_point,
    )

    animation = FuncAnimation(
        fig,
        update_positions,
        frames=range(0, len(values), 5),
        interval=50,
        blit=True
    )

    save_animation(animation, name)

    return 1


if __name__ == "__main__":
    main(sys.argv[1])
