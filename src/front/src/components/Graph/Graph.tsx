import { Line } from 'react-chartjs-2';
import useGraphHook from './Graph.hooks'

const Graph = () => {
  const { options, data } = useGraphHook();

  return (<div>
      <Line options={options} data={data} />
  </div>)
}

export default Graph;
