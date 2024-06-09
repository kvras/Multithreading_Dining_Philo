<h1>Dining Philosophers Problem</h1>

<p>This project is a multi-threaded C program that solves the classic concurrency problem known as the Dining Philosophers Problem.</p>

<h2>Description</h2>

<p>The Dining Philosophers Problem is a classic demonstration of a common computing problem - concurrency. The problem is a model for concurrent processes that either compete or cooperate for resources. In this case, the philosophers are threads and the resources are forks.</p>

<h2>Installation</h2>

<p>Clone the repository and compile the code using make.</p>

<pre>
<code>
git clone &lt;repository-url&gt;
cd &lt;repository-directory&gt;
make
</code>
</pre>

<h2>Usage</h2>

<p>Run the program with the following command:</p>

<pre>
<code>
./philosophers &lt;number_of_philosophers&gt; &lt;time_to_die&gt; &lt;time_to_eat&gt; &lt;time_to_sleep&gt; [number_of_times_each_philosopher_must_eat]
</code>
</pre>

<p>Where:</p>
<ul>
<li><code>number_of_philosophers</code>: The number of philosophers and also the number of forks.</li>
<li><code>time_to_die</code>: If a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.</li>
<li><code>time_to_eat</code>: The time it takes for a philosopher to eat. During that time he will need to keep the two forks.</li>
<li><code>time_to_sleep</code>: The time the philosopher will spend sleeping.</li>
<li><code>number_of_times_each_philosopher_must_eat</code>: If all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ times, the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.</li>
</ul>

<h2>Contributing</h2>

<p>Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.</p>

<h2>License</h2>

<p><a href="https://choosealicense.com/licenses/mit/">MIT</a></p>
