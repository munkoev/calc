import { Line } from 'react-chartjs-2';
import useGraphHook from './Graph.hooks'
import styles from './Graph.module.css'

const Graph = () => {
  const { options, data, err } = useGraphHook();

  return (<div className={styles.graph}>
      <div className={styles.err}>{err ? 'error' : ''}</div>
      <Line options={options} data={data} />
  </div>)
}

export default Graph;
