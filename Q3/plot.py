import matplotlib.pyplot as plt
import pandas as pd
df = pd.read_csv("data.csv")
print(df)
plt.plot(df["n"],df["sim"],c="r",label="Without multithreading")
plt.plot(df["n"],df["thd"],c="b",label="With multithreading")
plt.xlabel("Input Size")
plt.ylabel("Running time (s)")
plt.show()